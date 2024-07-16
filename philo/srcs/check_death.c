/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:28:56 by mbogey            #+#    #+#             */
/*   Updated: 2024/07/17 01:30:44 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died_or_full(t_philo *philo);

void	*check_death_or_full(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!check_all_philos_run(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		usleep(10);
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died_or_full(table->philos + i) == true)
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				safe_printf(table->philos, " died\n");
				set_bool(&table->printf_mutex, &table->can_write, false);
				usleep(50);
				break ;
			}
		}
		usleep(10);
	}
	return (NULL);
}

static bool	philo_died_or_full(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
	{
		set_bool(&philo->table->printf_mutex, &philo->table->can_write, false);
		return (true);
	}
	pthread_mutex_lock(&philo->philo_mutex);
	elapsed = gettime(philo->table) - philo->last_meal_time;
	pthread_mutex_unlock(&philo->philo_mutex);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}
