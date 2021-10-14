/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:09:05 by lugonzal          #+#    #+#             */
/*   Updated: 2021/10/14 11:50:54 by lugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>
#include <stdio.h>

size_t	num_process(char *str, bool *signal)
{
	size_t	out;

	out = 0;
	if (*signal)
		return (out);
	while (*str)
	{
		if (*str < 48 || *str > 57)
		{
			*signal = true;
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
	init_timer(&timer);
	if (set_values(argc, argv, &timer))
	{
		free_utils(&timer);
		return (2);
	}
	if (philo_dynamic(timer))
		return (3);
	free_utils(&timer);
	return (0);
}
