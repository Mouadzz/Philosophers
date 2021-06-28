/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 13:15:51 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/28 16:24:40 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_args
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	struct timeval	start_time;
	sem_t			*exit;
	sem_t			*for_write;
	sem_t			*forks;
	int				isalive;
	int				iseating;
	pid_t			*all_pid;
}	t_args;

typedef struct s_philo
{
	int				counter;
	int				count_forks;
	int				id;
	int				start_time_ms;
	t_args			*args;
	sem_t			*eating;
}	t_philo;

int		ft_isdigit(char *str);
int		ft_atoi(char *str);
char	*ft_itoa(int n);
int		ft_check(int n);
int		ft_strlen(char *str);
void	write_status(int id, char *str, t_philo *philo, int isalive);
int		time_to_ms(struct timeval current_time);
void	simulation(t_args *args);
void	my_sleep(long time);
void	routine(t_philo *philo);
void	*supervisord(void *arg);

#endif
