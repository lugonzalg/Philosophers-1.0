/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:46:35 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/10 20:40:57 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

bool	free_data(t_timer *timer)
{
	free(timer->fork);
	free(timer->mutex);
	return (true);
}

bool	set_values(int argc, char *argv[], t_timer *timer)
{
	size_t	signal;

	signal = 0;
	timer->size = num_process(argv[1], &signal);
	timer->die = num_process(argv[2], &signal);
	timer->eat = num_process(argv[3], &signal);
	timer->sleep = num_process(argv[4], &signal);
	if (argc == 6)
		timer->max = num_process(argv[5], &signal);
	if (signal)
		return (true);
	timer->fork = malloc(sizeof(bool) * timer->size);
	if (!timer->fork)
		return (true);
	timer->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!timer->mutex)
	{
		free(timer->fork);
		return (true);
	}
	memset(timer->fork, true, timer->size);
	return (false);
}
