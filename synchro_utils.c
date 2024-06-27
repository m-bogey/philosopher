#include "philo.h"

void    wait_all_threads(t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready))
        ;
}

bool    all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool    ret;

	//printf("th = %ld %ld\n" ,threads, philo_nbr);
    ret = false;
    safe_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
    safe_mutex(mutex, UNLOCK);
    return (ret);
}  

void    increase_long(t_mtx *mutex, long *value)
{
    safe_mutex(mutex, LOCK);
    (*value)++;
    safe_mutex(mutex, UNLOCK);
}