/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:03:59 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 10:35:00 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	help_routine(t_philo *philo)
{
	struct timeval	start_time_each;

	pthread_mutex_lock(&philo->args->forks[philo->id]);
	write_status(philo->id, "has taken a fork", philo, 0);
	pthread_mutex_lock(&philo->args->forks[(philo->id + 1) \
	% philo->args->number_of_philosophers]);
	write_status(philo->id, "has taken a fork", philo, 0);
	pthread_mutex_lock(&philo->eating);
	write_status(philo->id, "is eating", philo, 0);
	gettimeofday(&start_time_each, NULL);
	philo->start_time_ms = time_to_ms(start_time_each);
	my_sleep(philo->args->time_to_eat * 1000);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	pthread_t		sv;

	philo = (t_philo *)arg;
	pthread_create(&sv, NULL, (void *)supervisord, philo);
	while (philo->args->isalive != 1 && philo->args->iseating != 1)
	{
		help_routine(philo);
		philo->counter += 1;
		pthread_mutex_unlock(&philo->eating);
		pthread_mutex_unlock(&philo->args->forks[philo->id]);
		pthread_mutex_unlock(&philo->args->forks[(philo->id + 1) \
		% philo->args->number_of_philosophers]);
		if (philo->args->number_of_times_each_philosopher_must_eat > 0 \
		&& philo->counter >= \
		philo->args->number_of_times_each_philosopher_must_eat)
			return (0);
		write_status(philo->id, "is sleeping", philo, 0);
		my_sleep(philo->args->time_to_sleep * 1000);
		write_status(philo->id, "is thinking", philo, 0);
	}
	return (0);
}
