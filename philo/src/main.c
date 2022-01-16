/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:09:05 by lugonzal          #+#    #+#             */
/*   Updated: 2021/12/14 20:19:30 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void	ft_free_utils(void *t)
{
	t_timer	*t_in;

	t_in = (t_timer *)t;
	free(t_in->max);
	free(t_in->fork);
	free(t_in->mutex);
	free(t_in->status);
}

static size_t	ft_num_process(char *str, bool *signal)
{
	size_t	out;

	out = 0;
	if (*signal)
		return (out);
	while (*str)
	{
		if (*str < 48 || *str > 57)
		{
			*signal = true;
			return (out);
		}
		out = out * 10 + (*str - 48);
		str++;
	}
	return (out);
}

static void	ft_set_max(t_timer *timer, int argc, char *argv[], bool *signal)
{
	size_t	max;
	size_t	i;

	i = -1;
	if (argc == 6)
		max = ft_num_process(argv[5], signal);
	else
		max = -1;
	while (++i < timer->size)
		timer->max[i] = max;
}

static bool	ft_set_values(int argc, char *argv[], t_timer *t)
{
	bool	signal;

	signal = false;
	t->status = (bool *)malloc(sizeof(bool));
	*t->status = true;
	t->size = ft_num_process(argv[1], &signal);
	t->die = ft_num_process(argv[2], &signal);
	t->eat = ft_num_process(argv[3], &signal);
	t->sleep = ft_num_process(argv[4], &signal);
	t->max = (ssize_t *)malloc(sizeof(ssize_t) * t->size);
	ft_set_max(t, argc, argv, &signal);
	if (signal)
		return (true);
	t->fork = (bool *)malloc(sizeof(bool) * t->size);
	if (!t->fork)
		return (true);
	t->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * t->size);
	if (!t->lock)
		return (true);
	t->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!t->mutex)
		return (true);
	memset(t->fork, true, t->size);
	return (false);
}

int	main(int argc, char *argv[])
{
	t_timer	t;

	if (argc < 5 || argc > 6)
		return (1);
	memset(&t, 0, sizeof(t_timer));
	if (ft_set_values(argc, argv, &t))
	{
		ft_free_utils(&t);
		return (2);
	}
	if (ft_philo_dynamic(t))
		return (3);
	ft_free_utils(&t);
	return (0);
}
