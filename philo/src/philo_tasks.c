/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:46:35 by lugonzal          #+#    #+#             */
/*   Updated: 2021/12/12 22:35:02 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern bool	ft_fork_request(t_timer *t, size_t id)
{
	if (id == t->size)
		id = 0;
	pthread_mutex_lock(&t->lock[id]);
	if (!t->fork[id])
	{
		pthread_mutex_unlock(&t->lock[id]);
		return (false);
	}
	t->fork[id] = false;
	pthread_mutex_lock(t->mutex);
	printf("%ld %zu has taken the fork\n", ft_timestamp(t->ref), t->id);
	pthread_mutex_unlock(t->mutex);
	pthread_mutex_unlock(&t->lock[id]);
	return (true);
}

extern void	ft_fork_giveback(t_timer *t, size_t id)
{
	pthread_mutex_lock(&t->lock[id - 1]);
	t->fork[id - 1] = true;
	pthread_mutex_unlock(&t->lock[id - 1]);
	if (id == t->size)
		id = 0;
	pthread_mutex_lock(&t->lock[id]);
	t->fork[id] = true;
	pthread_mutex_unlock(&t->lock[id]);
}
