/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:10:23 by lugonzal          #+#    #+#             */
/*   Updated: 2021/12/06 21:05:35 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_timer
{
	bool			*status;
	sem_t			*sem;
	sem_t			*statuss;
	sem_t			*kill;
	sem_t			*max;
	struct timeval	*start;
	struct timeval	ref;
	size_t			max_count;
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
void	*dead_status(void *timer);
bool	philo_dynamic(t_timer timer);

#endif
