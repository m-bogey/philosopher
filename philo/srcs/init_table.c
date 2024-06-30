/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:22:51 by mbogey            #+#    #+#             */
/*   Updated: 2024/06/29 14:09:35 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	first_init(int ac, char **av, t_table *table);
static long	ft_atol(char *str);
static int	philo_init(t_table *table);
static void	assign_forks(t_philo *philo, t_fork *forks, int i);

int	init_table(int ac, char **av, t_table *table)
{
	int	i;

	i = -1;
	first_init(ac, av, table);
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (-1);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
		return (-2);
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (-3);
	if (pthread_mutex_init(&table->printf_mutex, NULL) != 0)
		return (-4);
	if (pthread_mutex_init(&table->stop_printf, NULL) != 0)
		return (-5);
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (-6);
		table->forks[i].is_available = true;
	}
	if (philo_init(table) == -1)
		return (-7);
	return (0);
}

static void	first_init(int ac, char **av, t_table *table)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (ac == 6)
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	table->start_simulation = -1;
	table->threads_running_nbr = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->can_write = true;
}

static long	ft_atol(char *str)
{
	size_t	i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	return (nb);
}

static int	philo_init(t_table *table)
{
	long	i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			return (-1);
		assign_forks(philo, table->forks, i);
		i++;
	}
	return (0);
}

static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % philo_nbr];
	}
	else
	{
		philo->left_fork = &forks[(i + 1) % philo_nbr];
		philo->right_fork = &forks[i];
	}
}
