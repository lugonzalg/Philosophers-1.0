/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 23:48:48 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/10 20:40:46 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/time.h>
#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool	first_eat(t_timer *timer, struct timeval *start)
{
	timer->fork[1] = false;
	timer->fork[0] = false;
	pthread_mutex_unlock(timer->mutex);
	printf("%ld %zu has taken the fork\n", timestamp(timer->ref), timer->id);
	gettimeofday(start, NULL);
	printf("%ld %zu is eating\n", timestamp(timer->ref), timer->id);
	usleep(timer->eat * 1000);
	timer->fork[1] = true;
	timer->fork[0] = true;
	return (false);
}

bool	mid_eat(t_timer *timer, struct timeval *start)
{
	timer->fork[timer->id - 1] = false;
	timer->fork[timer->id] = false;
	pthread_mutex_unlock(timer->mutex);
	printf("%ld %zu has taken the fork\n", timestamp(timer->ref), timer->id);
	gettimeofday(start, NULL);
	printf("%ld %zu is eating\n", timestamp(timer->ref), timer->id);
	usleep(timer->eat * 1000);
	timer->fork[timer->id - 1] = true;
	timer->fork[timer->id] = true;
	return (false);
}

bool	last_eat(t_timer *timer, struct timeval *start)
{
	timer->fork[timer->size - 1] = false;
	timer->fork[0] = false;
	printf("%ld %zu has taken the fork\n", timestamp(timer->ref), timer->id);
	pthread_mutex_unlock(timer->mutex);
	gettimeofday(start, NULL);
	printf("%ld %zu is eating\n", timestamp(timer->ref), timer->id);
	usleep(timer->eat * 1000);
	timer->fork[timer->size - 1] = true;
	timer->fork[0] = true;
	return (false);
}
