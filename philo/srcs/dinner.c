/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:26:45 by mbogey            #+#    #+#             */
/*   Updated: 2024/06/29 15:20:18 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		pthread_create(&table->philos[0].thread_id, NULL, // a proteger
			&if_one_philo, &table->philos[0]);
	else
	{
		while (++i < table->philo_nbr)
			if (pthread_create(&table->philos[i].thread_id, NULL,
					&routine, &table->philos[i]) != 0)
				return ;
	}
	if (table->philo_nbr > 1)
		if (pthread_create(&table->monitor, NULL,
				&check_death_or_full, table) != 0)
			return ;
	table->start_simulation = gettime(table);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			return ;
}

static void	*if_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(philo->table));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	if (safe_printf(philo, " has taken a fork\n") == -1)
		return (NULL);
	usleep(philo->table->time_to_die);
	safe_printf(philo->table->philos, " philo died\n");
	return (NULL);
}

static int	think(t_philo *philo)
{
	long	t_think;
	long	t_eat;
	long	t_sleep;

	if (safe_printf(philo, " is thinking\n") == -1)
		return (-1);
	if (philo->table->philo_nbr % 2 != 0)
	{
		t_eat = philo->table->time_to_eat;
		t_sleep = philo->table->time_to_sleep;
		t_think = t_eat * 2 - t_sleep;
	}
	else
		t_think = 0;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think, philo->table);
	return (0);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	if (safe_printf(philo, " has taken a fork\n") == -1)
		return (-1);
	pthread_mutex_lock(&philo->right_fork->fork);
	if (safe_printf(philo, " has taken a fork\n") == -1)
		return (-1);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(philo->table));
	philo->meals_counter++;
	if (safe_printf(philo, " is eating\n") == -1)
		return (-1);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	return (0);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(philo->table));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	if (philo->id % 2 == 0)
		think(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full == true)
			break ;
		if (eat(philo) == -1)
			break ;
		safe_printf(philo, " is sleeping\n");
		precise_usleep(philo->table->time_to_sleep, philo->table);
		if (think(philo) == -1)
			break ;
	}
	return (NULL);
}
