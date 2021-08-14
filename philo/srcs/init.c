/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:24:23 by vminomiy          #+#    #+#             */
/*   Updated: 2021/08/11 22:54:24 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_monitor(t_monitor *monitor)
{
	struct timeval	time;

	gettimeofday(&monitor->table->start, NULL);
	gettimeofday(&time, NULL);
	while (current_time(&time, &monitor->table->start) < 100000)
		gettimeofday(&time, NULL);
	gettimeofday(&monitor->table->start, NULL);
	pthread_mutex_unlock(&monitor->food);
}

void	init_phi(t_monitor *monitor)
{
	int	i;

	i = -1;
	while (++i < monitor->table->n)
	{
		monitor->philo[i].l_fork = &monitor->forks[0];
		if (i != monitor->table->n - 1)
			monitor->philo[i].l_fork = &monitor->forks[i];
		pthread_mutex_init(monitor->philo[i].l_fork, NULL);
		monitor->philo[i].r_fork = &monitor->forks[i];
		if (i != monitor->table->n - 1)
			monitor->philo[i].r_fork = &monitor->forks[i + 1];
		pthread_mutex_init(monitor->philo[i].r_fork, NULL);
		monitor->philo[i].alive = 1;
		monitor->philo[i].init = &monitor->init;
		monitor->philo[i].idx = i + 1;
		monitor->philo[i].table = monitor->table;
		monitor->philo[i].timestamp = &monitor->timestamp;
		pthread_mutex_init(&monitor->philo[i].death, NULL);
		pthread_mutex_init(&monitor->philo[i].take_fork, NULL);
		pthread_mutex_lock(&monitor->philo[i].take_fork);
		pthread_mutex_init(&monitor->philo[i].drop_fork, NULL);
		pthread_mutex_lock(&monitor->philo[i].drop_fork);
	}
}

/* Here will be decided who eats first odds or even */
void	init_queue(t_monitor *monitor)
{
	int	i;
	int	shift;

	i = 0;
	shift = 0;
	while (i < monitor->table->n)
	{
		monitor->queue[shift++] = i;
		i += 2;
	}
	i = 1;
	while (i < monitor->table->n)
	{
		monitor->queue[shift++] = i;
		i += 2;
	}
}

int	memalloc_struct(t_table **table, t_monitor **monitor, int n)
{
	size_t	size;
	void	*mem;

	size = sizeof(t_monitor) + sizeof(t_table) + n * (sizeof(t_philo)
			+ sizeof(t_philo *) + sizeof(pthread_mutex_t) + sizeof(int));
	mem = malloc(size);
	if (!mem)
		return (1);
	ft_memset(mem, 0, size);
	*table = mem;
	*monitor = mem + sizeof(t_table);
	(*monitor)->philo = (void *)(*monitor) + sizeof(t_monitor);
	(*monitor)->forks = (void *)(*monitor)->philo + sizeof(t_philo) * n;
	(*monitor)->queue = (void *)(*monitor)->forks + sizeof(pthread_mutex_t) * n;
	(*monitor)->table = *table;
	return (0);
}

int	init_table(t_table *table, int ac, char **av)
{
	int	tmp;

	table->t_meal = -1;
	table->n = ft_atoi(av[1]);
	tmp = ft_atoi(av[2]);
	table->t_die.tv_sec = tmp / 1000;
	table->t_die.tv_usec = tmp % 1000 * 1000;
	tmp = ft_atoi(av[3]);
	table->t_eat.tv_sec = tmp / 1000;
	table->t_eat.tv_usec = tmp % 1000 * 1000;
	tmp = ft_atoi(av[4]);
	table->t_slp.tv_sec = tmp / 1000;
	table->t_slp.tv_usec = tmp % 1000 * 1000;
	if (ac == 6)
		table->t_meal = ft_atoi(av[5]);
	return (0);
}
