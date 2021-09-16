/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 23:10:38 by vminomiy          #+#    #+#             */
/*   Updated: 2021/09/15 02:11:38 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

/*
**	As requested by the subject, the following options should be set as:
**
**	p_num == number_of_philosophers;
**	t_die == time_to_die;
**	t_eat == time_to_eat;
**	t_slp == time_to_sleep;
**	t_meal == number_of_times_each_philosopher_must_eat;
*/
typedef struct timeval	t_timeval;

typedef struct s_table
{
	int				n;
	t_timeval		start;
	t_timeval		t_die;
	t_timeval		t_eat;
	t_timeval		t_slp;
	int				t_meal;
}	t_table;

typedef struct s_philo
{
	int				alive;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	take_fork;
	pthread_mutex_t	drop_fork;
	pthread_mutex_t	death;
	pthread_mutex_t	*init;
	pthread_mutex_t	*timestamp;
	int				idx;
	int				fed;
	unsigned int	locks;
	t_table			*table;
	t_timeval		last_feed;
}	t_philo;

typedef struct s_monitor
{
	t_table			*table;
	t_philo			*philo;
	int				idx;
	pthread_mutex_t	*forks;
	int				*queue;
	int				work;
	pthread_mutex_t	init;
	pthread_mutex_t	food;
	pthread_mutex_t	timestamp;
}	t_monitor;

typedef struct s_status
{
	int				state;
	pthread_mutex_t	mutex;
}	t_status;

int				ft_atoi(const char *str);
int				ft_aredigit(char *str);
void			*ft_memset(void *b, int c, size_t len);
int				init_table(t_table *table, int ac, char **av);
int				memalloc_struct(t_table **table, t_monitor **monitor, int n);
int				validate_args(char **av);
void			init_queue(t_monitor *monitor);
void			init_monitor(t_monitor *monitor);
void			help(void);
void			init_phi(t_monitor *monitor);
void			*routine(void *philosofer);
unsigned long	current_time(struct timeval *t1, struct timeval *t2);
unsigned long	timeval_to_usec(struct timeval timeval);
void			take_forks(t_philo *phi);
void			*end_dinner(t_monitor *monitor);
void			*food_manager(void *monitor);
void			*monitor_manager(void *monitor);
void			display(t_philo *phi, char flag);

#endif
