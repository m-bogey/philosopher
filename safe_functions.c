#include "philo.h"

int	safe_printf(t_philo *philo, char *s)
{
	long	time;

	time = gettime(philo->table);
	if (pthread_mutex_lock(&philo->table->printf_mutex) != 0)
		return (-1);
	printf("%ld %d %s", time, philo->id ,s);
	if (pthread_mutex_unlock(&philo->table->printf_mutex) != 0)
		return (-1);
	return (0);
}
