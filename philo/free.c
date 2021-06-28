/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:27:30 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/26 13:22:29 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo **philo)
{
	int	i;
	int	max;

	max = philo[0]->args->number_of_philosophers;
	i = 0;
	while (i < max)
	{
		philo[i]->args = NULL;
		free(philo[i]);
		i += 1;
	}
	free(philo);
}

void	free_args(t_args *args)
{
	free(args->philosophers);
	free(args->forks);
	free(args);
}
