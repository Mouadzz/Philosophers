/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:03:12 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 10:40:26 by mlasrite         ###   ########.fr       */
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
	while (philo->args->isalive != 1 && philo->args->iseating != 1)
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
			break ;
		}
		pthread_mutex_unlock(&philo->eating);
		my_sleep(1000);
	}
	return (0);
}

int	is_all_eaten(t_philo **philo)
{
	int	i;
	int	max;
	int	philos;

	max = philo[0]->args->number_of_times_each_philosopher_must_eat;
	philos = philo[0]->args->number_of_philosophers;
	i = 0;
	while (i < philos)
	{
		if (philo[i]->counter < max && max > 0)
			return (1);
		i += 1;
	}
	return (0);
}

void	*supervisord_eat(void *arg)
{
	t_philo	**philo;
	int		res;

	philo = (t_philo **)arg;
	res = 0;
	while (philo[0]->args->isalive != 1 && philo[0]->args->iseating != 1)
	{
		my_sleep(1000);
		res = is_all_eaten(philo);
		if (res == 1)
			continue ;
		philo[0]->args->iseating = 1;
		pthread_mutex_unlock(&philo[0]->args->exit);
		break ;
	}
	return (0);
}
