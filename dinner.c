#include "philo.h"

static void	*if_one_philo(void *arg);
static int	think(t_philo *philo);
static int	eat(t_philo *philo);
static void	*routine(void *arg);

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		pthread_create(&table->philos[0].thread_id, NULL, &if_one_philo, &table->philos[0]);
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, &routine, &table->philos[i]);
	}
	pthread_create(&table->monitor, NULL, &check_death_or_full, table);
	table->start_simulation = gettime(table);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
}

static void	*if_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(philo->table));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	if (safe_printf(philo, " has taken a fork\n") == -1)
	{
		write(2, "error with mutex -- if_one_philo\n", 33);
		return (NULL);
	}
	usleep(philo->table->time_to_die);
	return (NULL);
}

static int	think(t_philo *philo)
{
	long	t_think;

	if (safe_printf(philo, " is thinking\n") == -1)
		return (-1);
	return (0);
}

static int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->left_fork->fork) != 0)
		return (-1);
	if (safe_printf(philo, " has taken a fork\n") == -1)
		return (-1);
	if (pthread_mutex_lock(&philo->right_fork->fork) != 0)
		return (-1);
	if (safe_printf(philo, " has taken a fork\n") == -1)
		return (-1);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(philo->table));
	philo->meals_counter++;
	if (safe_printf(philo, " is eating\n") == -1)
		return (-1);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	if (pthread_mutex_unlock(&philo->left_fork->fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(&philo->right_fork->fork) != 0)
		return (-1);
	return (0);
}

static void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(philo->table));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	while (1)
	{
		if (philo->full == true)
			break ;
		if (eat(philo) == -1)
		{
			write(2, "error with mutex -- eat\n", 24);
			break ;
		}
		safe_printf(philo, " is sleeping\n");
		precise_usleep(philo->table->time_to_sleep, philo->table);
		if (think(philo) == -1)
			break ;
	}
	return (NULL);
}
