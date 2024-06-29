#include "philo.h"

static bool philo_died_or_full(t_philo *philo);

void    *check_death_or_full(void *data)
{
    int i;
    t_table *table;

    table = (t_table *)data;
    while (!check_all_philos_run(&table->table_mutex,
		&table->threads_running_nbr, table->philo_nbr))
        ;
    while (!simulation_finished(table))
    {
        i = -1;
        while (++i < table->philo_nbr && !simulation_finished(table))
        {
            if (philo_died_or_full(table->philos + i) == true)
            {
                set_bool(&table->table_mutex, &table->end_simulation, true);
                safe_printf(table->philos, " died\n");
				exit(0); // verifier si exit la
            }
        }
    }
    return (NULL);
}

static bool philo_died_or_full(t_philo *philo)
{
    long    elapsed;
    long    t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = gettime(philo->table) - philo->last_meal_time;
    t_to_die = philo->table->time_to_die / 1000;
    if (elapsed > t_to_die)
        return (true);
    return (false);
}
