/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:38:04 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/14 12:06:43 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>

static bool	philo_eat(t_timer *t, struct timeval *start)
{
	printf("%ld %zu has taken the fork\n", timestamp(t->ref), t->id);
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
	return (false);
}

static bool	philo_query(t_timer *timer, struct timeval *start)
{
	size_t	i;

	i = -1;
	printf("PRE_IN_SEM ID: %zu\n", timer->id);
	while (++i < 2)
		sem_wait(timer->sem);
	printf("AF_IN_SEM ID: %zu\n", timer->id);
	philo_eat(timer, start);
	return (true);
}

static void	*start_process(void *timer)
{
	t_timer			timer_in;
	struct timeval	start[2];

	timer_in = *(t_timer *)timer;
	gettimeofday(&start[0], NULL);
	while (*timer_in.status)
	{
		printf("IN_LOOP ID: %zu\n", timer_in.id);
		while (*timer_in.status && philo_query(&timer_in, &start[0]))
			dead_status(start[0], &timer_in);
		printf("2IN_LOOP ID: %zu\n", timer_in.id);
		printf("%ld %zu is sleeping\n", timestamp(timer_in.ref), timer_in.id);
		if (!*timer_in.status || !timer_in.max)
			return (NULL);
		gettimeofday(&start[1], NULL);
		while ((long)timer_in.sleep > timestamp(start[1]))
			usleep(timer_in.sleep);
		usleep(250);
		printf("%ld %zu is thinking\n", timestamp(timer_in.ref), timer_in.id);
		usleep(250);
	}
	return (NULL);
}

bool	philo_dynamic(t_timer timer)
{
	size_t			i;	

	if (gettimeofday(&timer.ref, NULL) == -1)
		return (1);
	i = -1;
	while (++i < timer.size)
	{
		timer.pid[i] = fork();
		timer.id = i + 1;
		if (timer.pid[i] == 0)
			start_process(&timer);
		printf("CHILD CREATED\n");
	}
	printf("FAMILY CREEATED\n");
	i = -1;
	while (++i < timer.size)
	{
		printf("VALUE: %zu", i);
		waitpid(timer.pid[i], NULL, 0);
	}
	i = -1;
	return (false);
}
