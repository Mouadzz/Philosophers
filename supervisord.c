/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:03:12 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/25 14:00:10 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *supervisord(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	struct timeval current_time;
	int current_ms;
	int time_ms;

	while (1)
	{
		pthread_mutex_lock(&philo->eating);
		gettimeofday(&current_time, NULL);
		current_ms = time_to_ms(current_time);
		time_ms = current_ms - philo->start_time_ms;
		if (time_ms > philo->args->time_to_die)
		{
			philo->args->isalive = 1;
			philo->args->who_died = philo->id;
			pthread_mutex_unlock(&philo->args->exit);
			break;
		}
		pthread_mutex_unlock(&philo->eating);
		usleep(1000);
	}
	return 0;
}