#include "philo.h"

/*


void	*routine(void *arg)
{
	t_table *table;
	long	ms_ecoule;

	table = (t_table*)arg;
	while (1)
	{
		printf("Philo %d is thinking.\n", table->philos->id);
		pthread_mutex_lock(&table->forks[table->philos->id].fork);
		pthread_mutex_lock(&table->forks[(table->philos->id + 1) % table->philo_nbr].fork);
		usleep(2000000);
		ms_ecoule = gettime(table);
		printf("%ld Philo %d is eating.\n",ms_ecoule, table->philos->id);
		pthread_mutex_unlock(&table->forks[table->philos->id].fork);
		pthread_mutex_unlock(&table->forks[(table->philos->id + 1) % table->philo_nbr].fork);
	}
}

void	create_thread_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philos[i].thread_id, NULL, &routine, table);
		i++;
	}
	table->start_simulation = gettime(table);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		printf("i = %d\n",i);
		i++;
	}
}
*/
int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		error_exit("Wrong input\n");
	//pthread_mutex_init(&table.mutex, NULL);
	parsing(ac, av);
	init_table(ac, av, &table);
	dinner_start(&table);
	//pthread_mutex_destroy(&table.mutex);
}
