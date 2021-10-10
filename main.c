/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:09:05 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/10 20:40:44 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	num_process(char *str, size_t *signal)
{
	size_t	out;

	out = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			*signal = 1;
			return (out);
		}
		out = out * 10 + (*str - 48);
		str++;
	}
	return (out);
}

int	main(int argc, char *argv[])
{
	t_timer	timer;

	if (argc < 5 || argc > 6)
		return (1);
	if (set_values(argc, argv, &timer))
		return (2);
	if (philo_dynamic(timer))
		return (3);
	return (0);
}
