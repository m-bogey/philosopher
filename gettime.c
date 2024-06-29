#include "philo.h"

long	gettime(t_table *table)
{
	struct timeval tv;
	long	time;
	long	result;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "fail Gettime\n", 13);
		return (-1);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (table->start_simulation == -1)
		return (time);
	result = time - table->start_simulation;
	return (result);
}

int	precise_usleep(long usec, t_table *table)
{
	struct	timeval start;
	struct	timeval end;
	long	elapsed_time = 0;

	if (gettimeofday(&start, NULL))
	{
		write(2, "fail Gettime\n", 13);
		return (-1);
	}
	while (elapsed_time < usec)
	{
		if (simulation_finished(table))
			break ;
		usleep(50);
		if (gettimeofday(&end, NULL))
		{
			write(2, "fail Gettime\n", 13);
			return (-1);
		}
		elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
	}
}