#include "philo.h"

void    clean(t_table *table)
{
    t_philo *philo;
    int     i;

    i = -1;
    while (++i < table->philo_nbr)
    {
        philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
	}
	pthread_mutex_destroy(&table->printf_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	free(table->forks);
	free(table->philos);
}