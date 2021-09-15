#include "philo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include <time.h>
#include <pthread.h>

pthread_mutex_t mutex;

int	ft_isdigit(int c)
{
	if (c < 48 || (c > 57))
		return (0);
	return (1);
}

int	ft_atoi_signal(char *str, int *signal)
{
	int	out;
	
	out = 0;
	while (*str)
	{
		out = out * 10 + (*str - '0');
		if (!ft_isdigit(*str))
		{
			*signal = 1;
			return (out);
		}
		str++;
	}
	return (out);
}

t_philo	*ft_lstlast_p(t_philo *lst)
{
	t_philo	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next_p != NULL)
		last = last->next_p;
	return (last);
}

t_fork	*ft_lstlast_f(t_fork *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_p(t_philo **head, t_philo *new, t_philo **tail)
{
	t_philo	*tmp;

	tmp = *head;
	if (tmp)
	{
		tmp = ft_lstlast_p(tmp);
		tmp->next_p = new;
		new->prev_p = tmp;
		(*tail) = new;
		new->next_p = NULL;
	}
	else
	{
		(*head) = new;
		(*tail) = new;
	}
}

void	ft_lstadd_f(t_fork **head, t_fork *new, t_fork **tail)
{
	t_fork	*tmp;

	tmp = *head;
	if (tmp)
	{
		tmp = ft_lstlast_f(tmp);
		tmp->next = new;
		new->prev = tmp;
		(*tail) = new;
		new->next = NULL;
	}
	else
	{
		(*head) = new;
		(*tail) = new;
	}
}

t_philo	*ft_create_phi(char **argv, t_data *data)
{
	t_philo *phi;

	phi = (t_philo *)malloc(sizeof(t_philo));
	if (!phi)
		return (NULL);
	phi->time_die = ft_atoi_signal(argv[2], &data->signal);
	phi->time_eat = ft_atoi_signal(argv[3], &data->signal);
	phi->time_sleep = ft_atoi_signal(argv[4], &data->signal);
	phi->max_eat = ft_atoi_signal(argv[5], &data->signal);
	if (data->signal)
	{
		data->exit_status = 1;
		free(phi);
		return (NULL);
	}
	phi->prev_p = NULL;
	phi->next_p = NULL;
	phi->prev_f = NULL;
	phi->next_f = NULL;
	phi->status = 1;
	return (phi);
}

t_fork *ft_create_fork (void)
{
	t_fork *fork;

	fork = (t_fork*)malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->status = 1;
	fork->next = NULL;
	fork->prev = NULL;
	return (fork);
}

int	ft_atoi_alert(const char *str, int *signal)
{
	long	out;

	out = 0;
	while (*str)
	{
		out = out * 10 + (*str - 48);
		if (!ft_isdigit(*str))
		{
			*signal = 1;
			return (0);
		}
		str++;
	}
	return (out);
}

void	set_philo_fork(t_data *data)
{
	t_philo	*ref;

	ref = data->head_p;
	while (data->head_p)
	{
		data->head_p->next_f = data->head_f;
		data->head_p->prev_f = data->head_f->prev;
		data->head_p = data->head_p->next_p;
		data->head_f = data->head_f->next;
		if (data->head_p == ref)
			break ;
	}
}

void	clear_list(t_data *data)
{
	while (data->head_p)
	{
		free(data->head_p);
		data->head_p = data->head_p->next_p;
	}
	while (data->head_f)
	{
		free(data->head_f);
		data->head_f = data->head_f->next;
	}
}

void ft_create_lists(char **argv, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total)
	{
		data->new_p = ft_create_phi(argv, data);
		if (!data->new_p)
		{
			//clear_list(data);
			return ;
		}
		data->new_p->label = i + 1;
		ft_lstadd_p(&data->head_p, data->new_p, &data->tail_p);
		data->new_f = ft_create_fork();
		if (!data->new_f)
		{
			//clear_list(data);
			return ;
		}
		ft_lstadd_f(&data->head_f, data->new_f, &data->tail_f);
	}
	data->tail_f->next = data->head_f;
	data->tail_p->next_p = data->head_p;
	data->head_f->prev = data->tail_f;
	data->head_p->prev_p = data->head_p;
}

t_data *init_data(char *philo)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->total = ft_atoi_signal(philo, &data->signal);
	data->id = (pthread_t *)malloc(sizeof(pthread_t) * data->total);
	if (!data->id)
		return (NULL);
	data->head_p = NULL;
	data->head_f = NULL;
	data->tail_p = NULL;
	data->tail_f = NULL;
	data->new_p = NULL;
	data->signal = 0;
	data->exit_status = 0;
	return (data);
}

float	timestamp(t_philo *philo)
{
	float	total_ms;
	float	total_s;

	gettimeofday(&philo->end, NULL);
	total_ms =  (float)(philo->end.tv_usec - philo->start_ref->tv_usec) / 1000;
	total_s =  (float)(philo->end.tv_sec - philo->start_ref->tv_sec) * 1000;
	return (total_s + total_ms);
}

int	philosopher_eats(t_philo *philo)
{
	pthread_mutex_lock(&mutex);
	if (philo->next_f->status && philo->prev_f->status)
	{
		gettimeofday(&philo->start, NULL);
		printf("%.4f %d has taken the fork\n", timestamp(philo), philo->label);
		philo->next_f->status = 0;
		philo->prev_f->status = 0;
		pthread_mutex_unlock(&mutex);
		printf("%.4f %d is eating\n", timestamp(philo), philo->label);
		usleep(philo->time_eat * 1000);
		philo->next_f->status = 1;
		philo->prev_f->status = 1;
		return (0);
	}
	else
		pthread_mutex_unlock(&mutex);
	return (1);
}

void	dead_status(t_philo *philo)
{
	float	total_sec;
	float	total_ms;

	gettimeofday(&philo->end, NULL);
	total_ms =  (philo->end.tv_usec - philo->start.tv_usec) / 1000;
	total_sec =  (philo->end.tv_sec - philo->start.tv_sec) * 1000;
	if (total_sec + total_ms >= (float)philo->time_die)
	{
		printf("TOTAL: %f LABEL: %d", total_sec + total_ms, philo->label);
		exit(0);
		philo->status = 0;
	}
}

void	*philo_game(void *node)
{
	t_philo *philo;

	philo = (t_philo *)node;
	gettimeofday(&philo->start, NULL);
	while (1)
	{
		while (philosopher_eats(philo))
			dead_status(philo);
		printf("%.4f %d is sleeping\n", timestamp(philo), philo->label);
		usleep(philo->time_sleep * 1000);
	//	dead_status(philo);
		printf("%.4f %d is thinking\n", timestamp(philo), philo->label);
	}
		pthread_detach(philo->id);
		return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int	i;

	if (argc < 4)
		return (1);
	data = init_data(argv[1]);
	if (!data)
		return (2);
	ft_create_lists(argv, data);
	set_philo_fork(data);
	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&data->start, NULL);
	i = -1;
	while (++i < data->total)
	{
		data->head_p->mutex = data->mutex;
		data->head_p->start_ref = &data->start;
		if (pthread_create(&data->head_p->id, NULL, &philo_game, data->head_p))
			return (3);
		data->id[i] = data->head_p->id;
		data->head_p = data->head_p->next_p;
	}
	i = -1;
	while (++i < data->total)
	{
		if (pthread_join(data->id[i], NULL))
			return (4);
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
//printf("LEFT FORK: %d\n", philo->next_f->status);
//printf("RIGHT FORK: %d\n", philo->prev_f->status);
