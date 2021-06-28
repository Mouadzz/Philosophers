/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:35:28 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 16:24:42 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void even(t_args *args, t_philo **philo)
{
	int i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->counter = 0;
		philo[i]->id = i;
		philo[i]->args = args;
		philo[i]->count_forks = 0;
		philo[i]->args->all_pid[i] = fork();
		if (philo[i]->args->all_pid[i] == 0)
			routine(philo[i]);
		else
			i += 2;
	}
}

void odd(t_args *args, t_philo **philo)
{
	int i;

	i = 1;
	while (i < args->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->counter = 0;
		philo[i]->id = i;
		philo[i]->args = args;
		philo[i]->count_forks = 0;
		philo[i]->args->all_pid[i] = fork();
		if (philo[i]->args->all_pid[i] == 0)
			routine(philo[i]);
		else
			i += 2;
	}
}

void simulation(t_args *args)
{
	t_philo **philo;
	int i;

	philo = malloc(sizeof(t_philo *) * args->number_of_philosophers);
	args->all_pid = malloc(sizeof(pid_t) * args->number_of_philosophers);

	gettimeofday(&args->start_time, NULL);
	sem_unlink("philo_bonus_exit");
	args->exit = sem_open("philo_bonus_exit", O_CREAT, 0777, 0);

	sem_unlink("philo_bonus_for_write");
	args->for_write = sem_open("philo_bonus_for_write", O_CREAT, 0777, 1);

	sem_unlink("philo_forks_exit");
	args->forks = sem_open("philo_forks_exit", O_CREAT, 0777, args->number_of_philosophers);
	even(args, philo);
	my_sleep(500);
	odd(args, philo);
	sem_wait(args->exit);
	i = 0;
	while (i < args->number_of_philosophers)
		kill(args->all_pid[i++], SIGKILL);
}
