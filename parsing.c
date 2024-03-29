#include "philo.h"

static void	check_int(char *arg);
static void	ft_isdigit(char *str);
static void	check_int_max(char	*str);
static int	ft_strcmp_int(char	*str);

void	parsing(int ac, char **av)
{
    int	i;

	i = 1;
	while (i < ac)
	{
		check_int(av[i]);
		i++;
	}
}

static void	check_int(char *arg)
{
	ft_isdigit(arg);
	check_int_max(arg);
}

static void	ft_isdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			error_exit("arguments is not full digit\n");
		i++;
	}
}

static void	check_int_max(char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 10)
		error_exit("arguments superior to INT MAX");
	if (i == 10)
	{
		if (ft_strcmp_int(str) < 0)
			error_exit("arguments superior to INT MAX");
	}
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