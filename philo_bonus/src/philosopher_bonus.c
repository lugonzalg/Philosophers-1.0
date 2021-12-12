/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:38:04 by lugonzal          #+#    #+#             */
/*   Updated: 2021/12/06 21:05:29 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

static bool	philo_eat(t_timer *t, struct timeval *start)
{
	sem_wait(t->sem);
	sem_wait(t->sem);
	printf("%ld %zu has taken the fork\n", timestamp(t->ref), t->id);
	gettimeofday(start, NULL);
	if (t->max_count--)
		sem_post(t->max);
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
	sem_post(t->sem);
	sem_post(t->sem);
	return (false);
}

void	*start_process(t_timer *timer_in)
{
	struct timeval	start;
	pthread_t		id;
	size_t			max_count;

	max_count = timer_in->max_count;
	gettimeofday(timer_in->start, NULL);
	pthread_create(&id, NULL, dead_status, timer_in);
	while (1)
	{
		if (*timer_in->status)
			philo_eat(timer_in, timer_in->start);
		printf("%ld %zu is sleeping\n", timestamp(timer_in->ref), timer_in->id);
		gettimeofday(&start, NULL);
		while ((long)timer_in->sleep > timestamp(start))
			usleep(timer_in->sleep);
		printf("%ld %zu is thinking\n", timestamp(timer_in->ref), timer_in->id);
	}
	return (NULL);
}

static void	*max_status(void *timer)
{
	t_timer	t;
	size_t	i;

	i = 0;
	t = *(t_timer *)timer;
	while (1)
	{
		sem_wait(t.max);
		i++;
		if (i == t.max_count * t.size)
		{
			sem_post(t.kill);
			break ;
		}
	}
	return (NULL);
}

bool	philo_dynamic(t_timer timer)
{
	size_t			i;	
	pid_t			*id;
	pthread_t		pthr_id;

	id = (pid_t *)malloc(sizeof(pid_t) * (timer.size));
	if (gettimeofday(&timer.ref, NULL) == -1)
		return (1);
	i = -1;
	pthread_create(&pthr_id, NULL, max_status, &timer);
	while (++i < timer.size)
	{
		id[i] = fork();
		timer.id = i + 1;
		if (id[i] == 0)
			start_process(&timer);
	}
	i = -1;
	while (++i < timer.size)
	{
		sem_wait(timer.kill);
		kill(id[i], SIGKILL);
		sem_post(timer.kill);
	}
	free(id);
	return (false);
}
