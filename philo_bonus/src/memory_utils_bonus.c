/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:38:26 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/14 12:06:21 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	free_utils(void *timer)
{
	t_timer	*timer_in;

	timer_in = (t_timer *)timer;
	free(timer_in->max);
	free(timer_in->fork);
	free(timer_in->mutex);
	free(timer_in->status);
}

void	init_timer(t_timer *timer)
{
	timer->mutex = NULL;
	timer->status = NULL;
	timer->fork = NULL;
	timer->max = NULL;
}

static void	set_max(t_timer *timer, int argc, char *argv[], bool *signal)
{
	size_t	max;
	size_t	i;

	i = -1;
	if (argc == 6)
		max = num_process(argv[5], signal);
	else
		max = -1;
	while (++i < timer->size)
		timer->max[i] = max;
}

bool	set_values(int argc, char *argv[], t_timer *timer)
{
	bool	signal;

	signal = false;
	timer->status = (bool *)malloc(sizeof(bool));
	*timer->status = true;
	timer->size = num_process(argv[1], &signal);
	timer->die = num_process(argv[2], &signal);
	timer->eat = num_process(argv[3], &signal);
	timer->sleep = num_process(argv[4], &signal);
	timer->max = (ssize_t *)malloc(sizeof(ssize_t) * timer->size);
	set_max(timer, argc, argv, &signal);
	timer->pid = (pid_t *)malloc(sizeof(pid_t) * timer->size);
	if (signal)
		return (true);
	sem_unlink("fork");
	timer->sem = sem_open("fork", O_CREAT, 0660, timer->size);
	return (false);
}
