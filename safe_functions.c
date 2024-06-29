/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:14:11 by mbogey            #+#    #+#             */
/*   Updated: 2024/06/29 15:00:25 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_printf(t_philo *philo, char *s)
{
	long	time;

	time = gettime(philo->table);
	if (pthread_mutex_lock(&philo->table->printf_mutex) != 0)
		return (-1);
	if (philo->table->can_write == true)
		printf("%ld %d %s", time, philo->id, s);
	if (pthread_mutex_unlock(&philo->table->printf_mutex) != 0)
		return (-1);
	return (0);
}
