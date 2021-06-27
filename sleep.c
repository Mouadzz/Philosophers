/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 10:56:06 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/27 12:23:22 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(long time)
{
	struct timeval	start_time;
	struct timeval	current_time;
	long			start;
	long			current;
	long			updated_time;

	gettimeofday(&start_time, NULL);
	start = time_to_ms(start_time);
	if (time >= 60000)
		usleep(time - 30000);
	else
		usleep(time);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		current = time_to_ms(current_time);
		updated_time = current - start;
		if (updated_time >= (time / 1000))
			break ;
	}
}
