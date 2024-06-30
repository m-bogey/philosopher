/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:16:12 by mbogey            #+#    #+#             */
/*   Updated: 2024/06/29 13:16:14 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_int(char *arg);
static int	ft_isdigit(char *str);
static int	check_int_max(char	*str);
static int	ft_strcmp_int(char	*str);

int	parsing(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (check_int(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int	check_int(char *arg)
{
	if (ft_isdigit(arg) == -1)
		return (-1);
	if (check_int_max(arg) == -1)
		return (-1);
	return (0);
}

static int	ft_isdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			write(2, "arguments is not full digit\n", 28);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	check_int_max(char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 10)
	{
		write(2, "arguments superior to INT MAX\n", 30);
		return (-1);
	}
	if (i == 10)
	{
		if (ft_strcmp_int(str) < 0)
		{
			write(2, "arguments superior to INT MAX\n", 30);
			return (-1);
		}
	}
	return (0);
}

static int	ft_strcmp_int(char	*str)
{
	size_t	i;

	i = 0;
	while (TESTINTMAX[i])
	{
		if (TESTINTMAX[i] != str[i])
			return (TESTINTMAX[i] - str[i]);
		i++;
	}
	return (0);
}
