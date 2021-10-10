/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:32:15 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/10 20:11:08 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_timer
{
	bool			*fork;
	size_t			size;
	size_t			die;
	size_t			eat;
	size_t			sleep;
	size_t			max;
	struct timeval	ref;
	size_t			id;
	pthread_mutex_t	*mutex;
}	t_timer;

void	print(t_timer timer, int argc);

size_t	num_process(char *str, size_t *signal);
bool	set_values(int argc, char *argv[], t_timer *timer);
bool	philo_dynamic(t_timer timer);
bool	free_data(t_timer *timer);
long	timestamp(struct timeval ref);
void	dead_status(struct timeval start, t_timer timer, size_t id);
bool	mid_eat(t_timer *timer, struct timeval *start);
bool	first_eat(t_timer *timer, struct timeval *start);
bool	last_eat(t_timer *timer, struct timeval *start);

#endif
