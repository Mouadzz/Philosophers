/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 12:31:07 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 16:24:39 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char *ft_strjoin(char *s1, char *s2)
{
	char *p;
	int s1len;
	int s2len;
	int i;
	int j;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	p = (char *)malloc((s1len + s2len) * sizeof(char) + 1);
	if (p == 0)
		return (0);
	i = 0;
	while (s1len--)
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2len--)
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

char *generate_sem_name(t_philo *philo)
{
	char *tmp;
	char *name;

	tmp = ft_itoa(philo->id);
	name = ft_strjoin("philo_bonus_eating", tmp);
	free(tmp);
	return (name);
}

void routine(t_philo *philo)
{
	struct timeval start_time_each;
	pthread_t sv;
	char *name;

	name = generate_sem_name(philo);
	sem_unlink(name);
	philo->eating = sem_open(name, O_CREAT, 0777, 1);
	// free(name);
	gettimeofday(&start_time_each, NULL);
	philo->start_time_ms = time_to_ms(start_time_each);
	pthread_create(&sv, NULL, (void *)supervisord, philo);
	while (1)
	{
		sem_wait(philo->args->forks);
		philo->count_forks += 1;
		write_status(philo->id, "has taken a fork", philo, 0);
		sem_wait(philo->args->forks);
		philo->count_forks += 1;
		write_status(philo->id, "has taken a fork", philo, 0);
		sem_wait(philo->eating);
		write_status(philo->id, "is eating", philo, 0);
		gettimeofday(&start_time_each, NULL);
		philo->start_time_ms = time_to_ms(start_time_each);
		my_sleep(philo->args->time_to_eat * 1000);
		sem_post(philo->eating);
		philo->counter += 1;
		sem_post(philo->args->forks);
		philo->count_forks -= 1;
		sem_post(philo->args->forks);
		philo->count_forks -= 1;
		if (philo->args->number_of_times_each_philosopher_must_eat > 0 && philo->counter >= philo->args->number_of_times_each_philosopher_must_eat)
			exit (1);
		write_status(philo->id, "is sleeping", philo, 0);
		my_sleep(philo->args->time_to_sleep * 1000);
		write_status(philo->id, "is thinking", philo, 0);
	}
}
