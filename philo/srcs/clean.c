/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:13:06 by mbogey            #+#    #+#             */
/*   Updated: 2024/07/15 21:35:28 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	if (table->philo_nbr > 1 && table->nbr_limit_meals != 0)
		pthread_join(table->monitor, NULL);
	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		pthread_mutex_destroy(&table->forks[i].fork);
	}
	pthread_mutex_destroy(&table->printf_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->stop_printf);
	free(table->forks);
	free(table->philos);
}

void	clean_init(t_table *table, int err)
{
	t_philo	*philo;
	int		i;

	(void)philo;
	i = -1;
	if (err <= -7)
	{
		while (++i < table->philo_nbr)
		{
			philo = table->philos + i;
			pthread_mutex_destroy(&table->forks[i].fork);
		}
	}
	if (err <= -6)
		pthread_mutex_destroy(&table->stop_printf);
	if (err <= -5)
		pthread_mutex_destroy(&table->printf_mutex);
	if (err <= -4)
		pthread_mutex_destroy(&table->table_mutex);
	if (err <= -3)
		free(table->forks);
	if (err <= -2)
		free(table->philos);
}
