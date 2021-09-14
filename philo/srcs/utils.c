/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:08:44 by vminomiy          #+#    #+#             */
/*   Updated: 2021/09/15 00:43:33 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(char **av)
{
	int		i;

	i = -1;
	while (av[++i])
	{
		if (!ft_aredigit(av[i]))
			return (1);
	}
	return (0);
}

void	*end_dinner(t_monitor *monitor)
{
	int		i;

	monitor->work = 0;
	i = -1;
	while (++i < monitor->table->n)
	{
		monitor->philo[i].alive = 0;
		if ((monitor->philo[i].locks | 1))
			pthread_mutex_unlock(&monitor->philo[i].take_fork);
		if ((monitor->philo[i].locks | 2))
			pthread_mutex_unlock(monitor->philo[i].l_fork);
	}
	return (NULL);
}

void	take_forks(t_philo *phi)
{
	phi->locks |= 1;/* 0000 0001 */
	pthread_mutex_lock(&phi->take_fork);
	phi->locks |= 2;/* 0000 0010 => 0000 0011*/
	pthread_mutex_lock(phi->l_fork);
	display(phi, 'f');
	pthread_mutex_lock(phi->r_fork);
	display(phi, 'f');
	pthread_mutex_unlock(&phi->drop_fork);
}
