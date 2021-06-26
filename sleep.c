/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 10:56:06 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/26 12:56:23 by mlasrite         ###   ########.fr       */
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
	usleep(time - 20000);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		current = time_to_ms(current_time);
		updated_time = current - start;
		if (updated_time >= (time / 1000))
			break ;
	}
}
