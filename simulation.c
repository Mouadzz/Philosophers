/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:35:28 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/25 11:23:42 by mlasrite         ###   ########.fr       */
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
	current_ms = time_to_ms(current_time);
	start_ms = time_to_ms(philo->args->start_time);
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

void *supervisord(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	struct timeval current_time;
	int current_ms;
	int time_ms;
	int i;

	i = 0;

	while (1)
	{
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
		usleep(1000);
	}
	return 0;
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	pthread_t sv;
	struct timeval start_time_each;

	pthread_create(&sv, NULL, (void *)supervisord, philo);
	while (philo->args->isalive != 1)
	{
		pthread_mutex_lock(&philo->args->forks[philo->id]);
		pthread_mutex_lock(&philo->args->forks[(philo->id + 1) % philo->args->number_of_philosophers]);
		write_status(philo->id, "has taken a fork", philo);
		write_status(philo->id, "is eating", philo);
		gettimeofday(&start_time_each, NULL);
		philo->start_time_ms = time_to_ms(start_time_each);
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->args->forks[philo->id]);
		pthread_mutex_unlock(&philo->args->forks[(philo->id + 1) % philo->args->number_of_philosophers]);
		write_status(philo->id, "is sleeping", philo);
		usleep(philo->args->time_to_sleep * 1000);
		write_status(philo->id, "is thinking", philo);
		philo->counter += 1;
	}
	return 0;
}

int simulation(t_args *args)
{
	int i;
	t_philo **philo;
	struct timeval start_time_each;

	philo = malloc(sizeof(t_philo *) * args->number_of_philosophers);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	args->philosophers = malloc(sizeof(pthread_t) * args->number_of_philosophers);
	gettimeofday(&args->start_time, NULL);
	args->isalive = 0;
	args->who_died = 0;
	pthread_mutex_init(&args->exit, NULL);
	pthread_mutex_lock(&args->exit);
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
		gettimeofday(&start_time_each, NULL);
		philo[i]->start_time_ms = time_to_ms(start_time_each);
		pthread_create(&args->philosophers[i], NULL, (void *)routine, philo[i]);
		i += 1;
	}

	pthread_mutex_lock(&args->exit);
	// write_status(args->who_died, "died", philo[args->who_died]);
	write(1,"died\n", 5);

	i = 0;
	while (i < args->number_of_philosophers)
		pthread_mutex_destroy(&args->forks[i++]);
	return (0);
}
