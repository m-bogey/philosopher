#include "philo.h"

static bool philo_died(t_philo *philo)
{
    long    elapsed;
    long    t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = gettime(philo->table) - philo->last_meal_time;
    t_to_die = philo->table->time_to_die;
	//printf("ela %ld %ld last = %ld\n",elapsed, t_to_die/1000, philo->last_meal_time);
    if (elapsed > t_to_die / 1000)
        return (true);
    return (false);
}

void    *monitor_dinner(void *data)
{
    int i;
    t_table *table;

    table = (t_table *)data;
    while (!all_threads_running(&table->table_mutex,
		&table->threads_running_nbr, table->philo_nbr))
        ;
    while (!simulation_finished(table))
    {
        i = -1;
        while (++i < table->philo_nbr && !simulation_finished(table))
        {
            if (philo_died(table->philos + i))
            {
                set_bool(&table->table_mutex, &table->end_simulation, true);
                safe_printf(table->philos, " philo died\n");
				exit(0);
            }
        }
    }
    return (NULL);
}