#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		error_exit("Wrong input\n");
	parsing(ac, av);
	init_table(ac, av, &table);
}
