/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:46:35 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/14 11:51:14 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	free_utils(void *timer)
{
	t_timer	*timer_in;

	timer_in = (t_timer *)timer;
	free(timer_in->max);
	free(timer_in->fork);
	free(timer_in->mutex);
	free(timer_in->status);
}

void	init_timer(t_timer *timer)
{
	timer->mutex = NULL;
	timer->status = NULL;
	timer->fork = NULL;
	timer->max = NULL;
}

static void	set_max(t_timer *timer, int argc, char *argv[], bool *signal)
{
	size_t	max;
	size_t	i;

	i = -1;
	if (argc == 6)
		max = num_process(argv[5], signal);
	else
		max = -1;
	while (++i < timer->size)
		timer->max[i] = max;
}

bool	set_values(int argc, char *argv[], t_timer *timer)
{
	bool	signal;

	signal = false;
	timer->status = (bool *)malloc(sizeof(bool));
	*timer->status = true;
	timer->size = num_process(argv[1], &signal);
	timer->die = num_process(argv[2], &signal);
	timer->eat = num_process(argv[3], &signal);
	timer->sleep = num_process(argv[4], &signal);
	timer->max = (ssize_t *)malloc(sizeof(ssize_t) * timer->size);
	set_max(timer, argc, argv, &signal);
	if (signal)
		return (true);
	timer->fork = (bool *)malloc(sizeof(bool) * timer->size);
	if (!timer->fork)
		return (true);
	timer->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!timer->mutex)
		return (true);
	memset(timer->fork, true, timer->size);
	return (false);
}
