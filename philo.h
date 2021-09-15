#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>

typedef struct s_fork 
{
	struct s_fork	*prev;
	struct s_fork	*next;
	int				status;
}	t_fork;

typedef struct s_philo 
{
	struct s_philo	*prev_p;
	struct s_philo	*next_p;
	struct s_fork	*prev_f;
	struct s_fork	*next_f;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				max_eat;
	int				label;
	pthread_t		id;
	int				status;
	pthread_mutex_t mutex;
	struct timeval	start;
	struct timeval	end;
	struct timeval	*start_ref;
}	t_philo;

typedef struct s_data
{
	t_philo		*head_p;
	t_philo		*tail_p;
	t_philo		*new_p;
	t_fork		*head_f;
	t_fork		*tail_f;
	t_fork		*new_f;
	int			signal;
	pthread_t	*id;
	int			total;
	struct timeval	start;
	int			exit_status;
	pthread_mutex_t	mutex;
}	t_data;

void	printf_list(t_data data, char *str);

# endif
