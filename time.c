/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 23:44:04 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/10 20:40:46 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"
#include <stdio.h>

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

void	dead_status(struct timeval start, t_timer timer, size_t id)
{
	struct timeval	end;
	time_t			sec;
	suseconds_t		micro_s;
	long			total;

	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	micro_s = end.tv_usec - start.tv_usec;
	total = (long)sec * 1000 + (long)micro_s / 1000;
	if (total >= (long)timer.die)
	{
		printf("[%zu]TOTAL %lu TIMESTAMP %ld\n\n", id, total, timestamp(timer.ref));
		exit(0);
	}
}
