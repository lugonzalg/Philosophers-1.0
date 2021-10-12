/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:46:35 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/12 23:23:05 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	free_utils(void *timer)
{
	t_timer	*timer_in;

	timer_in = (t_timer *)timer;
	free(timer_in->fork);
	free(timer_in->mutex);
	free(timer_in->status);
}

bool	set_values(int argc, char *argv[], t_timer *timer)
{
	size_t	signal;

	signal = 0;
	timer->status = (bool *)malloc(sizeof(bool));
	*timer->status = 1;
	timer->size = num_process(argv[1], &signal);
	timer->die = num_process(argv[2], &signal);
	timer->eat = num_process(argv[3], &signal);
	timer->sleep = num_process(argv[4], &signal);
	if (argc == 6)
		timer->max = num_process(argv[5], &signal);
	else
		timer->max = -1;
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
