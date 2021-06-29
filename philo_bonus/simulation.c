/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:35:28 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/29 12:49:19 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo **philo)
{
	int	i;
	int	max;

	max = philo[0]->args->number_of_philosophers;
	i = 0;
	while (i < max)
	{
		philo[i]->args = NULL;
		free(philo[i]);
		i += 1;
	}
	free(philo);
}

void	even(t_args *args, t_philo **philo)
{
	int	i;

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

void	odd(t_args *args, t_philo **philo)
{
	int	i;

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

void	help_simulation(t_args *args, t_philo **philo)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < args->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0)
			break ;
		i += 1;
	}
	if (WEXITSTATUS(status) != 0)
	{
		sem_wait(args->for_write);
		write(1, "All philosophers have eaten !!\n", 31);
	}
	i = 0;
	while (i < args->number_of_philosophers)
		kill(args->all_pid[i++], SIGKILL);
	free_philo(philo);
	free(args->all_pid);
	free(args);
}

void	simulation(t_args *args)
{
	t_philo	**philo;

	philo = malloc(sizeof(t_philo *) * args->number_of_philosophers);
	args->all_pid = malloc(sizeof(pid_t) * args->number_of_philosophers);
	gettimeofday(&args->start_time, NULL);
	sem_unlink("philo_bonus_for_write");
	args->for_write = sem_open("philo_bonus_for_write", O_CREAT, 0777, 1);
	sem_unlink("philo_forks_exit");
	args->forks = sem_open("philo_forks_exit", \
	O_CREAT, 0777, args->number_of_philosophers);
	even(args, philo);
	my_sleep(1000);
	odd(args, philo);
	help_simulation(args, philo);
}
