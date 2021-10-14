/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 23:44:04 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/14 11:51:24 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>
#include <string.h>

long	timestamp(struct timeval ref)
{
	struct timeval	stamp;
	time_t			sec;
	suseconds_t		micro_s;

	gettimeofday(&stamp, NULL);
	sec = (stamp.tv_sec - ref.tv_sec) * 1000;
	micro_s = (stamp.tv_usec - ref.tv_usec) / 1000;
	return (sec + micro_s);
}

static bool	max_status(t_timer timer)
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

void	dead_status(struct timeval start, t_timer *timer)
{
	struct timeval	end;
	time_t			sec;
	suseconds_t		micro_s;
	long			total;

	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	micro_s = end.tv_usec - start.tv_usec;
	total = (long)sec * 1000 + (long)micro_s / 1000;
	if ((total >= (long)timer->die || max_status(*timer)) && *timer->status)
	{
		pthread_mutex_lock(timer->mutex);
		if (timer->max[timer->id - 1])
			printf("%ld %zu died\n", timestamp(timer->ref), timer->id);
		*timer->status = false;
		memset(timer->fork, false, timer->size);
		pthread_mutex_unlock(timer->mutex);
	}
}
