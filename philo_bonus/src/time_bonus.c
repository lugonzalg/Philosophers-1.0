/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:38:35 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/18 18:06:38 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void	*dead_status(void *timer)
{
	t_timer			timer_th;

	timer_th = *(t_timer *)timer;
	while (*timer_th.status)
	{
		sem_wait(timer_th.statuss);
		if (*timer_th.status
			&& (long)timer_th.die <= timestamp(*timer_th.start))
		{
			printf("%ld %zu died\n", timestamp(timer_th.ref), timer_th.id);
			sem_post(timer_th.kill);
			*timer_th.status = false;
			break ;
		}
		sem_post(timer_th.statuss);
	}
	return (NULL);
}
