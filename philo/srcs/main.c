/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:22:12 by mbogey            #+#    #+#             */
/*   Updated: 2024/06/29 13:22:13 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		err;

	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong input\n", 12);
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
