/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:23:40 by vminomiy          #+#    #+#             */
/*   Updated: 2021/09/16 20:19:48 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philosofer)
{
	t_philo	*phi;

	phi = philosofer;
	pthread_mutex_lock(phi->init);
	pthread_mutex_unlock(phi->init);
	display(phi, 'b');
	gettimeofday(&phi->last_feed, NULL);
	while (phi->alive)
	{
		take_forks(phi);
		pthread_mutex_lock(&phi->death);
		gettimeofday(&phi->last_feed, NULL);
		pthread_mutex_unlock(&phi->death);
		display(phi, 'e');
		++(phi->fed);
		usleep(timeval_to_usec(phi->table->t_eat));
		pthread_mutex_unlock(phi->r_fork);
		pthread_mutex_unlock(phi->l_fork);
		phi->locks &= ~2;
		display(phi, 's');
		usleep(timeval_to_usec(phi->table->t_slp));
		display(phi, 't');
	}
	return (NULL);
}

int	check_vitals(t_philo *phi)
{
	struct timeval	time;
	int				ret;

	ret = 1;
	pthread_mutex_lock(&phi->death);
	gettimeofday(&time, NULL);
	if ((current_time(&time, &phi->last_feed)
			> timeval_to_usec(phi->table->t_die))
		&& phi->last_feed.tv_sec != 0)
	{
		phi->alive = 0;
		ret = 0;
	}
	pthread_mutex_unlock(&phi->death);
	return (ret);
}

void	*monitor_manager(void *monitor)
{
	t_monitor	*mon;
	int			i;
	int			fed;

	mon = monitor;
	init_monitor(mon);
	while (1)
	{
		i = -1;
		fed = 0;
		while (++i < mon->table->n)
		{
			if ((mon->philo[i].last_feed.tv_sec != 0)
				&& !check_vitals(&mon->philo[i]))
			{
				display(&mon->philo[i], 'd');
				return (end_dinner(mon));
			}
			if (mon->philo[i].fed >= mon->table->t_meal)
				++fed;
		}
		if (mon->table->t_meal != -1 && fed >= mon->table->n)
			return (end_dinner(mon));
	}
}

void	*food_manager(void *monitor)
{
	t_monitor	*mon;
	int			i;
	int			tmp;

	mon = monitor;
	pthread_mutex_lock(&mon->food);
	i = -1;
	while (++i < mon->table->n)
		pthread_mutex_unlock(mon->philo[mon->queue[i]].init);
	while (mon->work)
	{
		i = mon->queue[mon->idx];
		pthread_mutex_unlock(&mon->philo[i].take_fork);
		mon->philo[i].locks &= ~1;
		pthread_mutex_lock(&mon->philo[i].drop_fork);
		tmp = ++(mon->idx) % mon->table->n;
		mon->idx = tmp;
	}
	return (NULL);
}
