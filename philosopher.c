/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:09:16 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/10 20:40:45 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

static bool	philo_query(t_timer *timer, struct timeval *start)
{
	pthread_mutex_lock(timer->mutex);
	if (timer->id != 1 && timer->id != timer->size)
	{
		usleep(40);
		if (timer->fork[timer->id - 1] && timer->fork[timer->id])
			return (mid_eat(timer, start));
	}
	else if (timer->id == 1)
	{
		usleep(40);
		if (timer->size != 1 && timer->fork[0] && timer->fork[1])
			return (first_eat(timer, start));
	}
	else
	{
		usleep(40);
		if (timer->fork[timer->id - 1] && timer->fork[0])
			return (last_eat(timer, start));
	}
	pthread_mutex_unlock(timer->mutex);
	return (true);
}

static void	*start_process(void *timer)
{
	t_timer			timer_in;
	struct timeval	start;
	
	timer_in = *(t_timer *)timer;
	pthread_mutex_unlock(timer_in.mutex);
	gettimeofday(&start, NULL);
	while (1)
	{
		while (philo_query(&timer_in, &start))
			dead_status(start, timer_in, timer_in.id);
		printf("%ld %zu is sleeping\n", timestamp(timer_in.ref), timer_in.id);
		usleep(timer_in.sleep * 1000);
		printf("%ld %zu is thinking\n", timestamp(timer_in.ref), timer_in.id);
	}
	return (NULL);
}

bool	philo_dynamic(t_timer timer)
{
	size_t			i;	
	pthread_t		*thread_id;
	pthread_mutex_t	mutex;

	thread_id = (pthread_t *)malloc(sizeof(pthread_t) * timer.size);
	if (!thread_id)
		return (1);
	pthread_mutex_init(&mutex, NULL);
	timer.mutex = &mutex;
	if (gettimeofday(&timer.ref, NULL) == -1)
		return (1);
	i = -1;
	while (++i < timer.size)
	{
		pthread_mutex_lock(&mutex);
		timer.id = i + 1;
		pthread_create(&thread_id[i], NULL, start_process, &timer);
	}
	i = -1;
	while (++i < timer.size)
		pthread_join(thread_id[i], NULL);
	return (false);
}
