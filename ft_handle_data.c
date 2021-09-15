int	ft_isdigit(int c)
{
	if (c < '0' && c > '9')
		return (0);
	return (1);
}

int	ft_atoi_signl(char *num, int *signal)
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
}

void	ft_handle_data(t_data * data, char *philo)
{
	int	i;

	i = -1;
	data->philo = ft_atoi_signal(philo, &data->sognal);
	//////CHANGE_THIS
	if (data->signal)
		exit (0);
	data->philo_id = (pthread_t *)malloc(sizeof(pthread_t) * data->philo);
}
