/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:05:45 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/29 11:01:40 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(int id, char *str, t_philo *philo, int isalive)
{
	struct timeval	current_time;
	int				time_ms;
	int				current_ms;
	int				start_ms;
	char			*tmp;

	gettimeofday(&current_time, NULL);
	current_ms = time_to_ms(current_time);
	start_ms = time_to_ms(philo->args->start_time);
	time_ms = current_ms - start_ms;
	sem_wait(philo->args->for_write);
	tmp = ft_itoa(time_ms);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
	tmp = NULL;
	write(1, " ", 1);
	tmp = ft_itoa(id + 1);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
	tmp = NULL;
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	if (isalive == 0)
		sem_post(philo->args->for_write);
}

int	time_to_ms(struct timeval current_time)
{
	int	current_ms;

	current_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (current_ms);
}
