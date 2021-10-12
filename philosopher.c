/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:09:16 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/12 23:23:04 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

bool	philo_eat(t_timer *timer, struct timeval *start, size_t	lf, size_t rf)
{
	timer->fork[lf] = false;
	timer->fork[rf] = false;
	printf("%ld %zu has taken the fork\n", timestamp(timer->ref), timer->id);
	if (timer->max != -1)
		timer->max--;
	pthread_mutex_unlock(timer->mutex);
	gettimeofday(start, NULL);
	printf("%ld %zu is eating\n", timestamp(timer->ref), timer->id);
	if (timer->eat < timer->die)
	{
		while ((long)timer->eat > timestamp(*start))
			usleep(timer->eat);
	}
	else
	{
		while ((long)timer->die > timestamp(*start))
			usleep(timer->die);
	}
	timer->fork[lf] = true;
	timer->fork[rf] = true;
	return (false);
}

static bool	philo_query(t_timer *timer, struct timeval *start)
{
	if (timer->id != 1 && timer->id != timer->size)
	{
		pthread_mutex_lock(timer->mutex);
		if (timer->fork[timer->id - 1] && timer->fork[timer->id])
			return (philo_eat(timer, start, timer->id, timer->id - 1));
	}
	else if (timer->id == 1)
	{
		pthread_mutex_lock(timer->mutex);
		if (timer->size != 1 && timer->fork[0] && timer->fork[1])
			return (philo_eat(timer, start, 1, 0));
	}
	else
	{
		pthread_mutex_lock(timer->mutex);
		if (timer->fork[timer->id - 1] && timer->fork[0])
			return (philo_eat(timer, start, 0, timer->id - 1));
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
	while (*timer_in.status)
	{
		while (*timer_in.status && philo_query(&timer_in, &start))
			dead_status(start, &timer_in);
		dead_status(start, &timer_in);
		if (!*timer_in.status || !timer_in.max)
			return (NULL);
		printf("%ld %zu is sleeping\n", timestamp(timer_in.ref), timer_in.id);
		printf("ID: %zu MAX: %zd\n", timer_in.id, timer_in.max);
		usleep(timer_in.sleep * 1000);
		printf("%ld %zu is thinking\n", timestamp(timer_in.ref), timer_in.id);
		dead_status(start, &timer_in);
		if (!*timer_in.status || !timer_in.max)
			return (NULL);
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
	i = -1;
	free(thread_id);
	return (false);
}
