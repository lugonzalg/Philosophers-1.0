#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

int	ft_isdigit(int c)
{
	if (c < '0' && c > '9')
		return (0);
	return (1);
}

int	ft_atoi_signal(char *str, int *signal)
{
	int	out;
	
	out = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			*signal = 1;
			return (out);
		}
		out = out * 10 + (*str + '0');
		str++;
	}
	return (out);
}

t_data	*ft_init_data(char *philo)
{
	int	i;
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	data->signal = 0;
	i = -1;
	data->total = ft_atoi_signal(philo, &data->signal);
	//////CHANGE_THIS
	if (data->signal)
		exit (0);
	data->philo_id = (pthread_t)malloc(sizeof(pthread_t) * data->total);
	return (data);
}

t_list	*init_list(void)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	list->data = 1;
	list->next = NULL;
	return (list);
}
void	*process(void *thread)
{
	t_list *list;
	
	list = (t_list *)thread;
	printf("Outer thread data-> %d\n", list->data);
	list->data++;
	//sleep(1);
	(void)thread;
	pthread_exit(NULL);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_list	*list;
	t_data *data;
	int	i;

	if (argc < 4)
		return (1);
	i = 0;
	list = init_list();
	data = ft_init_data(argv[1]);
	pthread_mutex_init(&mutex, NULL);
	while (i < data->total)
	{
		data->signal = pthread_create(&t1, NULL, &process, (void *)list);
		if (data->signal)
		{
			printf("Something went wrong");
			return (2);
		}
		i++;
	}
	pthread_mutex_destroy(&mutex, NULL);
	printf("Main thread data access -> %d\n", list->data);
	pthread_join(t1, NULL);
	printf("Main thread data acces -> %d\n", list->data);
	return (0);
}
