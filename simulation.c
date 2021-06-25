/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:35:28 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/25 15:00:12 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void simulation_2(t_args *args, t_philo **philo)
{
	int i;
	struct timeval start_time_each;

	pthread_mutex_init(&args->for_write, NULL);
	pthread_mutex_init(&args->exit, NULL);
	pthread_mutex_lock(&args->exit);

	i = 0;
	while (i < args->number_of_philosophers)
		pthread_mutex_init(&args->forks[i++], NULL);

	i = 0;
	while (i < args->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->counter = 0;
		philo[i]->id = i;
		philo[i]->args = args;
		pthread_mutex_init(&philo[i]->eating, NULL);
		gettimeofday(&start_time_each, NULL);
		philo[i]->start_time_ms = time_to_ms(start_time_each);
		pthread_create(&args->philosophers[i], NULL, (void *)routine, philo[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < args->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->counter = 0;
		philo[i]->id = i;
		philo[i]->args = args;
		pthread_mutex_init(&philo[i]->eating, NULL);
		gettimeofday(&start_time_each, NULL);
		philo[i]->start_time_ms = time_to_ms(start_time_each);
		pthread_create(&args->philosophers[i], NULL, (void *)routine, philo[i]);
		i += 2;
	}
	pthread_mutex_lock(&args->exit);
}

void simulation(t_args *args)
{
	int i;
	t_philo **philo;

	philo = malloc(sizeof(t_philo *) * args->number_of_philosophers);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	args->philosophers = malloc(sizeof(pthread_t) * args->number_of_philosophers);
	gettimeofday(&args->start_time, NULL);
	simulation_2(args, philo);
	write_status(args->who_died, "died", philo[args->who_died], 1);
	i = 0;
	while (i < args->number_of_philosophers)
		pthread_mutex_destroy(&args->forks[i++]);
	i = 0;
	while (i < args->number_of_philosophers)
		pthread_mutex_destroy(&philo[i++]->eating);
	pthread_mutex_destroy(&args->exit);
	pthread_mutex_destroy(&args->for_write);
	free_philo(philo);
	free_args(args);
}
