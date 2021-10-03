/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:32:26 by vminomiy          #+#    #+#             */
/*   Updated: 2021/10/02 21:35:40 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	help(void)
{
	printf("A few hints to run the simulation.\n");
	printf("This project need to have 5 or 6 arguments.\n");
	printf("- The first one, should be the programm \"./philo-one\".\n");
	printf("- Followed by 4 mandatory arguments:\n");
	printf("	- The number of philosofers in the table.\n");
	printf("	- The amount of time for someone to starve.\n");
	printf("	- The amount of time each one takes to eat, using 2 forks.\n");
	printf("	- The amount of time each one takes to sleep.\n");
	printf("**All timed arguments are set in Milisseconds.\n");
	printf("- You may also set the number of times each philosofer should\n");
	printf("eat, although this is optional. By default the simulation\n");
	printf("will stop when one philosofer dies or everyone eats their fill.\n");
	printf("For example: \"./philo 4 410 200 200 5\".\n");
	exit(EXIT_SUCCESS);
}

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
		msg = "is thinking";
	if (get_status()->state != 1)
	{
		pthread_mutex_lock(&get_status()->mutex);
		time = (current_time(get_timestamp(phi), &phi->table->start)) / 1000;
		printf("%09lu %03d %s.\n", time, phi->idx, msg);
		pthread_mutex_unlock(&get_status()->mutex);
		if (flag == 'd')
			get_status()->state = 1;
	}
}
