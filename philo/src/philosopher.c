/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:09:16 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/18 17:21:33 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/philo.h"

static bool	philo_eat(t_timer *t, struct timeval *start, size_t	lf, size_t rf)
{
	t->fork[lf] = false;
	t->fork[rf] = false;
	printf("%ld %zu has taken the fork\n", timestamp(t->ref), t->id);
	pthread_mutex_unlock(t->mutex);
	if (t->max[t->id - 1] != -1)
		t->max[t->id - 1]--;
	gettimeofday(start, NULL);
	printf("%ld %zu is eating\n", timestamp(t->ref), t->id);
	if (t->eat < t->die)
	{
		while ((long)t->eat > timestamp(*start))
			usleep(t->eat);
	}
	else
	{
		while ((long)t->die > timestamp(*start))
			usleep(t->die);
	}
	pthread_mutex_lock(t->mutex);
	t->fork[lf] = true;
	t->fork[rf] = true;
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
	struct timeval	start[2];

	timer_in = *(t_timer *)timer;
	pthread_mutex_unlock(timer_in.mutex);
	gettimeofday(&start[0], NULL);
	while (*timer_in.status)
	{
		while (*timer_in.status && philo_query(&timer_in, &start[0]))
			dead_status(start[0], &timer_in);
		dead_status(start[0], &timer_in);
		if (!*timer_in.status)
			break ;
		printf("%ld %zu is sleeping\n", timestamp(timer_in.ref), timer_in.id);
		pthread_mutex_unlock(timer_in.mutex);
		gettimeofday(&start[1], NULL);
		while ((long)timer_in.sleep > timestamp(start[1]))
			usleep(timer_in.sleep);
		printf("%ld %zu is thinking\n", timestamp(timer_in.ref), timer_in.id);
		usleep(1100);
		dead_status(start[0], &timer_in);
	}
	pthread_mutex_unlock(timer_in.mutex);
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
	pthread_mutex_destroy(timer.mutex);
	free(thread_id);
	return (false);
}
