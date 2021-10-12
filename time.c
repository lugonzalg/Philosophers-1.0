/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 23:44:04 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/12 23:23:07 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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
	if ((total >= (long)timer->die || timer->max == 0) && *timer->status)
	{
		pthread_mutex_lock(timer->mutex);
		if (timer->max)
			printf("%ld %zu died\n", timestamp(timer->ref), timer->id);
		*timer->status = 0;
		memset(timer->fork, false, timer->size);
		pthread_mutex_unlock(timer->mutex);
	}
}
