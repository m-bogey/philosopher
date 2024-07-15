/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_one_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:26:45 by mbogey            #+#    #+#             */
/*   Updated: 2024/07/16 00:43:57 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*if_one_philo(void *arg)
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
