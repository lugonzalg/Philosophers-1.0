/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:32:15 by lugonzal          #+#    #+#             */
/*   Updated: 2021/12/14 16:20:02 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_timer
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*lock;
	bool			*status;
	bool			*fork;
	ssize_t			*max;
	struct timeval	ref;
	size_t			size;
	size_t			die;
	size_t			eat;
	size_t			sleep;
	size_t			id;
}	t_timer;

extern long	ft_timestamp(struct timeval ref);
extern void	ft_dead_status(struct timeval start, t_timer *timer);
extern int	ft_philo_dynamic(t_timer timer);
extern bool	ft_fork_request(t_timer *t, size_t id);
extern void	ft_fork_giveback(t_timer *t, size_t id);

#endif
