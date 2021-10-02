/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:50:32 by vminomiy          #+#    #+#             */
/*   Updated: 2021/09/16 22:03:00 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	timeval_to_usec(struct timeval timeval)
{
	return (timeval.tv_sec * 1000000 + timeval.tv_usec);
}

unsigned long	current_time(struct timeval *t1, struct timeval *t2)
{
	unsigned long	usec;
	unsigned long	sec;

	sec = t1->tv_sec - t2->tv_sec;
	usec = t1->tv_usec - t2->tv_usec;
	return (sec * 1000000 + usec);
}
