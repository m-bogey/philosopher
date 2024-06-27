#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>    //printf
#include <stdlib.h>   // malloc free
#include <unistd.h>   // usleep
#include <stdbool.h>  // voir si utilise bool
#include <pthread.h>  // mutex: init destroy lock unlock
					  // threads: create join detach
#include <sys/time.h> // gettimeofday
#include <limits.h>	  // INT_MAX
#include <errno.h>

# define TESTINTMAX "2147483647"

typedef pthread_mutex_t t_mtx;

typedef struct s_table	t_table;

typedef enum	e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_code;

typedef struct	s_fork
{
	t_mtx	fork;
	bool	is_available;
}				t_fork;

typedef struct	s_philo
{
		int		id;
		long	meals_counter;
		bool	full;
		long	last_meal_time; // time passed from last meal
		t_fork	*left_fork;
		t_fork	*right_fork;
		pthread_t	thread_id; // philo is a thread
		t_mtx		philo_mutex;
		t_table		*table;
}				t_philo;

typedef struct s_table
{
		t_mtx	mutex;
		long	time;
		long	philo_nbr;
		long	time_to_die;
		long	time_to_eat;
		long	time_to_sleep;
		long	nbr_limit_meals; // [5]
		long	start_simulation;
		bool	end_simulation; // philo dies or all philos full
		bool	all_threads_ready; // attendre que tout les threads soit pret
		long	threads_running_nbr;
		pthread_t	monitor;
		t_mtx	table_mutex;
		t_mtx	write_mutex;
		t_fork	*forks; // array forks
		t_philo	*philos; // array thinks
}				t_table;

void    error_exit(const char *error);
void	parsing(int ac, char **av);
void    init_table(int ac, char **av, t_table *table);
void	*safe_malloc(size_t bytes);
void	safe_mutex(t_mtx *mutex, t_code code);
void	safe_printf(t_philo *philo, char *s);
long	gettime(t_table *table);
void    dinner_start(t_table *table);

void    set_bool(t_mtx *mutex, bool *dest, bool value);
bool    get_bool(t_mtx *mutex, bool *value);
bool    get_long(t_mtx *mutex, long *value);
void    set_long(t_mtx *mutex, long *dest, long value);
bool    simulation_finished(t_table *table);

void    wait_all_threads(t_table *table);
void	precise_usleep(long usec, t_table *table);

bool    all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void    increase_long(t_mtx *mutex, long *value);

void    *monitor_dinner(void *data);
#endif