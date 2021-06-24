/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:35:28 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/24 18:18:50 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void write_status(int id, char *str, t_philo *philo)
{
	struct timeval current_time;
	int time_ms;
	int current_ms;
	int start_ms;

	gettimeofday(&current_time, NULL);
	current_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	start_ms = (philo->args->start_time.tv_sec * 1000) + (philo->args->start_time.tv_usec / 1000);
	time_ms = current_ms - start_ms;
	pthread_mutex_lock(&philo->args->for_write);
	write(1, ft_itoa(time_ms), ft_strlen(ft_itoa(time_ms)));
	write(1, " ", 1);
	write(1, ft_itoa(id), ft_strlen(ft_itoa(id)));
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->args->for_write);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	// while (1)
	// {
		pthread_mutex_lock(&philo->args->forks[philo->id]);
		pthread_mutex_lock(&philo->args->forks[(philo->id + 1) % philo->args->number_of_philosophers]);
		write_status(philo->id, "has taken a fork", philo);
		write_status(philo->id, "is eating", philo);
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->args->forks[philo->id]);
		pthread_mutex_unlock(&philo->args->forks[(philo->id + 1) % philo->args->number_of_philosophers]);
		write_status(philo->id, "is sleeping", philo);
		usleep(philo->args->time_to_sleep * 1000);
		write_status(philo->id, "is thinking", philo);
	// }
	return 0;
}

int simulation(t_args *args)
{
	int i;
	t_philo **philo;

	philo = malloc(sizeof(t_philo *) * args->number_of_philosophers);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	args->philosophers = malloc(sizeof(pthread_t) * args->number_of_philosophers);
	gettimeofday(&args->start_time, NULL);

	i = 0;
	while (i < args->number_of_philosophers)
		pthread_mutex_init(&args->forks[i++], NULL);
	pthread_mutex_init(&args->for_write, NULL);

	i = 0;
	while (i < args->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->counter = 0;
		philo[i]->id = i;
		philo[i]->args = args;
		pthread_create(&args->philosophers[i], NULL, (void *)routine, philo[i]);
		i += 1;
	}

	while (1)
	{
	}

	i = 0;
	while (i < args->number_of_philosophers)
		pthread_mutex_destroy(&args->forks[i++]);

	return (0);
}
