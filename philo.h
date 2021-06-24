/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 13:15:51 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/24 18:16:20 by mlasrite         ###   ########.fr       */
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
} t_args;

typedef struct s_philo
{
	int isalive;
	int counter;
	int id;
	t_args *args;
} t_philo;

int ft_isdigit(char *str);
void print_struct(t_args *head);
int ft_atoi(char *str);
int simulation(t_args *args);
void *routine(void *arg);
char *ft_itoa(int n);
int ft_check(int n);
int ft_strlen(char *str);

#endif