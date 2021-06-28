/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 12:31:07 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 13:17:43 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		s1len;
	int		s2len;
	int		i;
	int		j;

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

void	routine(t_philo *philo)
{
	struct timeval start_time_each;
	pthread_t		sv;
	// char *tmp;

	// sem_unlink("philo_bonus_exit");
	// philo->eating = ("philo_bonus_exit", O_CREAT, 0777, 0);

	pthread_create(&sv, NULL, (void *)supervisord, philo);
	while (1)
	{
		sem_wait(philo->args->forks);
		write_status(philo->id, "has taken a fork", philo, 0);
		sem_wait(philo->args->forks);
		write_status(philo->id, "has taken a fork", philo, 0);
		//
		write_status(philo->id, "is eating", philo, 0);
		gettimeofday(&start_time_each, NULL);
		philo->start_time_ms = time_to_ms(start_time_each);
		my_sleep(philo->args->time_to_eat * 1000);
		//
		// philo->counter += 1;
		sem_post(philo->args->forks);
		sem_post(philo->args->forks);
		// if (philo->args->number_of_times_each_philosopher_must_eat > 0 && philo->counter >= philo->args->number_of_times_each_philosopher_must_eat)
		// 	break;
		write_status(philo->id, "is sleeping", philo, 0);
		my_sleep(philo->args->time_to_sleep * 1000);
		write_status(philo->id, "is thinking", philo, 0);
	}
}
