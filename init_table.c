#include "philo.h"

static long    ft_atol(char *str);

static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;

	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	long	i;
	t_philo *philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	init_table(int ac, char **av, t_table *table)
{
	int	i;

	i = 0;
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (ac == 6)
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	// check si les time to doivent etre superieur a 60000 -> 60ms?
	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i; //super for debug
		i++;
	}
	philo_init(table);
}

static long    ft_atol(char *str)
{
    size_t  i;
    long    nb;

    i = 0;
    nb = 0;
    while (str[i])
    {
        nb = (nb * 10) + (str[i] - 48); 
        i++;
    }
    return (nb);
}