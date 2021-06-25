/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 13:15:51 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/25 14:13:19 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_args
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_t *philosophers;
	pthread_mutex_t *forks;
	pthread_mutex_t for_write;
	struct timeval start_time;
	pthread_mutex_t exit;
	int isalive;
	int who_died;
} t_args;

typedef struct s_philo
{
	int counter;
	int id;
	int	start_time_ms;
	t_args *args;
	pthread_mutex_t eating;
} t_philo;

int ft_isdigit(char *str);
int ft_atoi(char *str);
char *ft_itoa(int n);
int ft_check(int n);
int ft_strlen(char *str);

void write_status(int id, char *str, t_philo *philo, int isalive);
int time_to_ms(struct timeval current_time);

void simulation(t_args *args);

void *supervisord(void *arg);
void *routine(void *arg);

void free_philo(t_philo **philo);
void free_args(t_args *args);

// segfault
// arg 5
// timer
// norm

#endif