/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:09:16 by lugonzal          #+#    #+#             */
/*   Updated: 2022/01/16 16:57:40 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void	ft_philo_eat(t_timer *t, struct timeval *start)
{
	if (t->max[t->id - 1] != -1)
		t->max[t->id - 1]--;
	pthread_mutex_lock(t->mutex);
	printf("%ld %zu is eating\n", ft_timestamp(t->ref), t->id);
	pthread_mutex_unlock(t->mutex);
	gettimeofday(start, NULL);
	if (t->eat < t->die)
	{
		while ((long)t->eat > ft_timestamp(*start))
			usleep(t->eat);
	}
	else
	{
		while ((long)t->die > ft_timestamp(*start))
			usleep(t->die);
	}
}

static int	ft_philo_query(t_timer *t, struct timeval *start)
{
	if (ft_fork_request(t, t->id))
	{
		while (*t->status && !ft_fork_request(t, t->id - 1))
			ft_dead_status(*start, t);
		ft_philo_eat(t, start);
		ft_fork_giveback(t, t->id);
		return (0);
	}
	return (1);
}

static int	ft_sleep(t_timer *t, struct timeval start[2])
{
	ft_dead_status(start[0], t);
	if (!*t->status)
		return (1);
	pthread_mutex_lock(t->mutex);
	printf("%ld %zu is sleeping\n", ft_timestamp(t->ref), t->id);
	pthread_mutex_unlock(t->mutex);
	gettimeofday(&start[1], NULL);
	while ((long)t->sleep > ft_timestamp(start[1]))
		usleep(t->sleep);
	if (!*t->status)
		return (1);
	pthread_mutex_lock(t->mutex);
	printf("%ld %zu is thinking\n", ft_timestamp(t->ref), t->id);
	pthread_mutex_unlock(t->mutex);
	ft_dead_status(start[0], t);
	return (0);
}

static void	*ft_start_process(void *t)
{
	t_timer			t_in;
	struct timeval	start[2];

	t_in = *(t_timer *)t;
	pthread_mutex_unlock(t_in.mutex);
	gettimeofday(&start[0], NULL);
	while (1)
	{
		if ((0.1 * t_in.size) < ft_timestamp(t_in.ref))
			break ;
		usleep(t_in.size * 2.5);
	}
	if ((t_in.id + 1) % 2)
		usleep(t_in.size * 70);
	while (*t_in.status)
	{
		while (*t_in.status && ft_philo_query(&t_in, &start[0]))
			ft_dead_status(start[0], &t_in);
		ft_sleep(&t_in, start);
	}
	pthread_mutex_unlock(t_in.mutex);
	return (NULL);
}

extern int	ft_philo_dynamic(t_timer t)
{
	size_t			i;	
	pthread_t		*thread_id;

	thread_id = (pthread_t *)malloc(sizeof(pthread_t) * t.size);
	if (!thread_id)
		return (1);
	pthread_mutex_init(t.mutex, NULL);
	if (gettimeofday(&t.ref, NULL) == -1)
		return (1);
	i = -1;
	while (++i < t.size)
	{
		pthread_mutex_init(&t.lock[i], NULL);
		pthread_mutex_lock(t.mutex);
		t.id = i + 1;
		pthread_create(&thread_id[i], NULL, ft_start_process, &t);
	}
	i = -1;
	while (++i < t.size)
	{
		pthread_join(thread_id[i], NULL);
		pthread_mutex_destroy(&t.lock[i]);
	}
	i = -1;
	pthread_mutex_destroy(t.mutex);
	free(thread_id);
	return (0);
}
