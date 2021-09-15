/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:04:26 by lugonzal          #+#    #+#             */
/*Updated: 2021/08/30 17:04:29 by lugonzal               ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

void	printf_list(t_data data, char *str)
{
	struct s_philo *ref_p;
	struct s_fork *ref_f;

	printf("\n\033[1;32m//////////////////////////////////////////\033[0;m\n");
	printf("\033[1;32m\tSORT, DOING %s\033[0;m\n", str);
	printf("\033[1;32m//////////////////////////////////////////\033[0;m\n");
	if (data.head_p)
	{
		printf("\n\033[1;34mPHILOSOPHER_LABEL: %d\033[0;m", data.head_p->label);
		printf("\t\t\033[1;34mPHILOSOPHER_ADDRESS: %p\033[0;m\n", data.head_p);
		printf("\n\033[1;34mLAST PHILOSOPHER_LABEL: %d\033[0;m", data.tail_p->label);
		printf("\t\t\033[1;34mLAST PHILOSOPHER ADDRES: %p\033[0;m\n", data.tail_p);
	}
	else
		printf("\n\033[1;34mNULLSOPHER\033[0;m\n\n");
	if (data.head_f)
	{
		printf("\n\033[1;34mFORK_STATUS: %d\033[0;m", data.head_f->status);
		printf("\t\t\033[1;34mHEAD FORK ADDRESS: %p\033[0;m\n", data.head_f);
		printf("\n\033[1;34mwLAST TAIL_STAUTS: %d\033[0;m", data.tail_f->status);
		printf("\t\t\033[1;34mLAST TAIL_ADDRESS: %p\033[0;m\n", data.tail_f);
	}
	else
		printf("\n\033[1;34mNULL FORK\033[0;m\n\n");
	printf("\033[1;31m__________________________\033[0;m\n");
	printf("\033[1;31m\tPHILOSOPHERS\033[0;m\n");
	printf("\033[1;31m--------------------------\033[0;m\n");
	if (!data.head_p)
		printf("\033[1;31m\tNONE\033[0;m\n");
	else
	{
		ref_p = data.head_p;
		while (data.head_p)
		{
			printf("LABEL:\t%d\n",data.head_p->label);
			if (data.head_p->next_f)
				printf("LEFT FORK:\t%p\n",data.head_p->next_f);
			if (data.head_p->prev_f)
				printf("RIGHT FORK:\t%p\n",data.head_p->prev_f);
			data.head_p = data.head_p->next_p;
			if (data.head_p == ref_p)
				break ;
		}
	}
	printf("\n\n\033[1;31m__________________________\033[0;m\n");
	printf("\033[1;31m\tFORKS B\033[0;m\n");
	printf("\033[1;31m--------------------------\033[0;m\n");
	if (!data.head_f)
		printf("\033[1;31m\tNONE\033[0;m\n");
	else
	{
		ref_f = data.head_f;
		while (data.head_f)
		{
			printf("FORK_STATUS:\t%d\n", data.head_f->status);
			data.head_f = data.head_f->next;
			if (data.head_f == ref_f)
				break ;
		}
	}
}
