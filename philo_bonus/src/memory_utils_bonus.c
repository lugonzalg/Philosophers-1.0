/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:38:26 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/18 18:06:38 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <stdlib.h>
#include <unistd.h>

void	free_utils(void *timer)
{
	t_timer	*timer_in;

	timer_in = (t_timer *)timer;
	free(timer_in->status);
	free(timer_in->start);
	sem_close(timer_in->sem);
	sem_close(timer_in->kill);
	sem_close(timer_in->max);
}

void	init_timer(t_timer *timer)
{
	timer->status = NULL;
	timer->start = NULL;
	timer->sem = NULL;
	timer->kill = NULL;
	timer->max = NULL;
}

static void	set_max(t_timer *timer, int argc, char *argv[], bool *signal)
{
	if (argc == 6)
		timer->max_count = num_process(argv[5], signal);
	else
		return ;
	sem_unlink("max");
	timer->max = sem_open("max", O_CREAT, 0660, 0);
}

bool	set_values(int argc, char *argv[], t_timer *timer)
{
	bool	signal;

	signal = false;
	timer->size = num_process(argv[1], &signal);
	timer->die = num_process(argv[2], &signal);
	timer->eat = num_process(argv[3], &signal);
	timer->sleep = num_process(argv[4], &signal);
	set_max(timer, argc, argv, &signal);
	if (signal)
		return (true);
	timer->status = (bool *)malloc(sizeof(bool));
	*timer->status = true;
	timer->start = (struct timeval *)malloc(sizeof(struct timeval));
	sem_unlink("fork");
	timer->sem = sem_open("fork", O_CREAT, 0660, timer->size);
	sem_unlink("kill");
	timer->kill = sem_open("kill", O_CREAT, 0660, 0);
	sem_unlink("statuss");
	timer->statuss = sem_open("statuss", O_CREAT, 0660, 1);
	return (false);
}
