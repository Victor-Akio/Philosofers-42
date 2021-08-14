/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:37:47 by vminomiy          #+#    #+#             */
/*   Updated: 2021/08/11 22:49:45 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dinner_time(t_monitor *monitor, int n)
{
	pthread_t	mon;
	pthread_t	food;
	int			i;

	monitor->work = 1;
	monitor->table->n = n;
	pthread_mutex_init(&monitor->init, NULL);
	pthread_mutex_init(&monitor->timestamp, NULL);
	pthread_mutex_lock(&monitor->init);
	pthread_mutex_init(&monitor->food, NULL);
	pthread_mutex_lock(&monitor->food);
	init_queue(monitor);
	init_phi(monitor);
	pthread_create(&mon, NULL, monitor_manager, monitor);
	pthread_create(&food, NULL, food_manager, monitor);
	i = -1;
	while (++i < monitor->table->n)
		pthread_create(&monitor->philo[i].thread, NULL,
			routine, &monitor->philo[i]);
	i = -1;
	while (++i < monitor->table->n)
		pthread_join(monitor->philo[i].thread, NULL);
	pthread_join(mon, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	t_table		*table;
	t_monitor	*monitor;
	int			ret;

	ret = 0;
	if (strcmp(av[1], "--help") == 0)
		help();
	if (ac > 6 || ac < 5 || !validate_args(av) || ft_atoi(av[1]) == 0)
	{
		printf("Error - Invalid arguments.\n");
		return (1);
	}
	if (!memalloc_struct(&table, &monitor, ft_atoi(av[1])))
		ret = init_table(table, ac, av);
	if (!ret)
		ret = dinner_time(monitor, ft_atoi(av[1]));
	else
		printf("Error - Memmory allocation or inicialization.\n");
	free(monitor->table);
	return (ret);
}
