/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:22:12 by mbogey            #+#    #+#             */
/*   Updated: 2024/07/16 01:10:45 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_zero(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '0' && av[i][1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		err;

	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong input\n", 12);
		return (0);
	}
	if (check_zero(ac, av) == 1)
	{
		write(2, "0 is bad input\n", 15);
		return (0);
	}
	if (parsing(ac, av) == -1)
		return (0);
	err = init_table(ac, av, &table);
	if (err < 0)
	{
		clean_init(&table, err);
		return (-1);
	}
	dinner(&table);
	clean(&table);
	return (0);
}
