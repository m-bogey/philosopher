/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:18:41 by mbogey            #+#    #+#             */
/*   Updated: 2024/07/16 00:42:29 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define TESTINTMAX "2147483647"

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			is_available;
}				t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}				t_philo;

typedef struct s_table
{
	long			time;
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_limit_meals;
	long			start_simulation;
	bool			end_simulation;
	bool			all_threads_ready;
	long			threads_running_nbr;
	pthread_t		monitor;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	stop_printf;
	t_fork			*forks;
	t_philo			*philos;
	bool			can_write;
}				t_table;

int		parsing(int ac, char **av);
int		init_table(int ac, char **av, t_table *table);
int		safe_printf(t_philo *philo, char *s);
long	gettime(t_table *table);
void	dinner(t_table *table);

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
bool	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

void	wait_philos(t_table *table);
int		precise_usleep(long usec, t_table *table);

bool	check_all_philos_run(pthread_mutex_t *mutex, long *threads,
			long philo_nbr);
void	increase_long(pthread_mutex_t *mutex, long *value);

void	*check_death_or_full(void *data);
void	clean(t_table *table);
void	clean_init(t_table *table, int err);
void	join_philos(t_table *table);

void	*if_one_philo(void *arg);
#endif
