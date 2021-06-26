/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:35:28 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/26 13:22:30 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	odd(t_args *args, t_philo **philo)
{
	int				i;
	struct timeval	start_time_each;

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
}

void	even(t_args *args, t_philo **philo)
{
	int				i;
	struct timeval	start_time_each;

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
}

void	simulation_2(t_args *args, t_philo **philo)
{
	int	i;

	pthread_mutex_init(&args->for_write, NULL);
	pthread_mutex_init(&args->exit, NULL);
	pthread_mutex_lock(&args->exit);
	i = 0;
	while (i < args->number_of_philosophers)
		pthread_mutex_init(&args->forks[i++], NULL);
	even(args, philo);
	my_sleep(1000);
	odd(args, philo);
	pthread_mutex_lock(&args->exit);
}

void	simulation(t_args *args)
{
	int		i;
	t_philo	**philo;

	philo = malloc(sizeof(t_philo *) * args->number_of_philosophers);
	args->forks = malloc(sizeof(pthread_mutex_t) \
	* args->number_of_philosophers);
	args->philosophers = malloc(sizeof(pthread_t) \
	* args->number_of_philosophers);
	gettimeofday(&args->start_time, NULL);
	simulation_2(args, philo);
	if (args->isalive == 1)
		write_status(args->who_died, "died", philo[args->who_died], 1);
	else if (args->iseating == 1)
		write(1, "All philosophers have eaten\n", 28);
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
