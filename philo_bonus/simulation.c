/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:35:28 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 13:17:45 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void even(t_args *args, t_philo **philo)
{
	int i;
	struct timeval start_time_each;
	pid_t pid;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->counter = 0;
		philo[i]->id = i;
		philo[i]->args = args;
		gettimeofday(&start_time_each, NULL);
		philo[i]->start_time_ms = time_to_ms(start_time_each);
		pid = fork();
		if (pid == 0)
			routine(philo[i]);
		else
			i += 2;
	}
}

void odd(t_args *args, t_philo **philo)
{
	int i;
	struct timeval start_time_each;
	pid_t pid;

	i = 1;
	while (i < args->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->counter = 0;
		philo[i]->id = i;
		philo[i]->args = args;
		gettimeofday(&start_time_each, NULL);
		philo[i]->start_time_ms = time_to_ms(start_time_each);
		pid = fork();
		if (pid == 0)
			routine(philo[i]);
		else
			i += 2;
	}
}

void simulation(t_args *args)
{
	t_philo **philo;

	philo = malloc(sizeof(t_philo *) * args->number_of_philosophers);
	sem_unlink("philo_bonus_exit");
	args->exit = ("philo_bonus_exit", O_CREAT, 0777, 0);
	sem_unlink("philo_forks_exit");
	args->forks = ("philo_forks_exit", O_CREAT, 0777, args->number_of_philosophers);
	even(args, philo);
	my_sleep(1000);
	odd(args, philo);
	sem_wait(args->exit);
}
