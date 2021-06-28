/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:03:12 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 16:24:40 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *supervisord(void *arg)
{
	struct timeval current_time;
	t_philo *philo;
	int current_ms;
	int time_ms;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->eating);
		gettimeofday(&current_time, NULL);
		current_ms = time_to_ms(current_time);
		time_ms = current_ms - philo->start_time_ms;
		if (time_ms > philo->args->time_to_die)
		{
			philo->args->isalive = 1;
			write_status(philo->id, "died", philo, 1);
			while (philo->count_forks > 0)
			{
				sem_post(philo->args->forks);
				philo->count_forks -= 1;
			}
			sem_post(philo->args->exit);
			exit(1);
		}
		sem_post(philo->eating);
	}
	return (0);
}
