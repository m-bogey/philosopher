#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with malloc");
	return (ret);
}

static void	mutex_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (code == LOCK || code == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (EINVAL == status && code == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the tread blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory to create another mutex.");
	else if (EBUSY == status)
		error_exit("MUTEX is locked");
}

void	safe_mutex(t_mtx *mutex, t_code code)
{
	if (code == LOCK)
		mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex), code);
	else
		error_exit("Wrong code for mutex");
}

void	safe_printf(t_philo *philo, char *s)
{
	long	time;

	time = gettime(philo->table);
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%ld %d %s", time, philo->id ,s);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
