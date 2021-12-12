/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 23:44:04 by lugonzal          #+#    #+#             */
/*   Updated: 2021/12/12 22:37:28 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long	ft_timestamp(struct timeval ref)
{
	struct timeval	stamp;
	time_t			sec;
	suseconds_t		micro_s;

	gettimeofday(&stamp, NULL);
	sec = (stamp.tv_sec - ref.tv_sec) * 1000;
	micro_s = (stamp.tv_usec - ref.tv_usec) / 1000;
	return (sec + micro_s);
}

static bool	ft_max_status(t_timer timer)
{
	size_t	i;

	i = 0;
	if (timer.max[timer.id - 1])
		return (false);
	else
	{
		while (i < timer.size && !timer.max[i])
			i++;
		if (i == timer.size)
			return (true);
	}
	return (false);
}

void	ft_dead_status(struct timeval start, t_timer *timer)
{
	usleep(1000);
	if ((ft_timestamp(start) >= (long)timer->die
			|| ft_max_status(*timer)) && *timer->status)
	{
		pthread_mutex_lock(timer->mutex);
		if (timer->max[timer->id - 1])
			printf("%ld %zu died\n", ft_timestamp(timer->ref), timer->id);
		*timer->status = false;
		memset(timer->fork, false, timer->size);
		pthread_mutex_unlock(timer->mutex);
		exit(0);
	}
}
