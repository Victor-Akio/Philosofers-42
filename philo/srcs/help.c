/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:53:28 by vminomiy          #+#    #+#             */
/*   Updated: 2021/08/11 22:49:42 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	call_help(char *str)
{
	printf("ERROR - %s.\n", str);
	printf("Use \"./philo --help\", if you have any doubts.\n");
	exit(EXIT_FAILURE);
}

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
	printf("For example: \"./philo 4 410 200 200\".\n");
	exit(EXIT_SUCCESS);
}
