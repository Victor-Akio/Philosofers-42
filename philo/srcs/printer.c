/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:32:26 by vminomiy          #+#    #+#             */
/*   Updated: 2021/08/11 22:46:30 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timeval	*get_timestamp(t_philo *philo)
{
	static t_timeval	time;

	pthread_mutex_lock(philo->timestamp);
	gettimeofday(&time, NULL);
	pthread_mutex_unlock(philo->timestamp);
	return (&time);
}

t_status	*get_status(void)
{
	static t_status		status;
	static int			new = 1;

	if (new)
	{
		new = 0;
		status.state = 0;
		pthread_mutex_init(&status.mutex, NULL);
	}
	return (&status);
}

void	display(t_philo *phi, char flag)
{
	unsigned long	time;
	char			*msg;

	if (flag == 'f')
		msg = "has taken a fork";
	else if (flag == 'e')
		msg = "is eating";
	else if (flag == 's')
		msg = "is sleeping";
	else if (flag == 't')
		msg = "is thinking";
	else if (flag == 'd')
		msg = "died";
	else if (flag == 'b')
		msg = "Philosofer initialized";
	if (get_status()->state != 1)
	{
		pthread_mutex_lock(&get_status()->mutex);
		time = (current_time(get_timestamp(phi), &phi->table->start)) / 1000;
		printf("%lu ms %03d %s.\n", time, phi->idx, msg);
		pthread_mutex_unlock(&get_status()->mutex);
		if (flag == 'd')
			get_status()->state = 1;
	}
}
