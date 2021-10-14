/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:10:23 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/14 12:10:58 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_timer
{
	sem_t			*sem;
	pthread_mutex_t	*mutex;
	bool			*status;
	bool			*fork;
	pid_t			*pid;
	ssize_t			*max;
	struct timeval	ref;
	size_t			size;
	size_t			die;
	size_t			eat;
	size_t			sleep;
	size_t			id;
}	t_timer;

size_t	num_process(char *str, bool	*signal);
void	init_timer(t_timer *timer);
bool	set_values(int argc, char *argv[], t_timer *timer);
void	free_utils(void *timer);
long	timestamp(struct timeval ref);
void	dead_status(struct timeval start, t_timer *timer);
bool	philo_dynamic(t_timer timer);

#endif
