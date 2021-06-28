/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:03:12 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 13:17:44 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisord(void *arg)
{
	struct timeval		current_time;
	t_philo				*philo;
	int					current_ms;
	int					time_ms;

	philo = (t_philo *)arg;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		current_ms = time_to_ms(current_time);
		time_ms = current_ms - philo->start_time_ms;
		if (time_ms > philo->args->time_to_die)
		{
			philo->args->isalive = 1;
			philo->args->who_died = philo->id;
			sem_post(philo->args->exit);
			return (0);
		}
		// my_sleep(1000);
	}
	return (0);
}
