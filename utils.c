/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 13:15:20 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/25 10:31:34 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i += 1;
	}
	return (0);
}

int ft_atoi(char *str)
{
	int i;
	int sign;
	long res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		if (res > 2147483648 && sign == -1)
			return (0);
		if (res > 2147483647 && sign == 1)
			return (-1);
		i++;
	}
	return (res * sign);
}

void print_struct(t_args *head)
{
	printf("%d\n", head->number_of_philosophers);
	printf("%d\n", head->time_to_die);
	printf("%d\n", head->time_to_eat);
	printf("%d\n", head->time_to_sleep);
	printf("%d\n", head->number_of_times_each_philosopher_must_eat);
}

int ft_check(int n)
{
	int i;
	unsigned int res;

	i = 1;
	res = n;
	if (n < 0)
	{
		i++;
		res *= -1;
	}
	while (res > 9)
	{
		res = res / 10;
		i++;
	}
	return (i);
}

char *ft_itoa(int n)
{
	int i;
	unsigned char *str;
	unsigned int res;

	res = n;
	i = ft_check(n);
	str = (unsigned char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		res = -1;
	}
	str[i] = '\0';
	while (--i && res >= 10)
	{
		str[i] = (res % 10) + 48;
		res = res / 10;
	}
	if (res < 10)
		str[i] = res % 10 + 48;
	return ((char *)str);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i += 1;
	return i;
}

int time_to_ms(struct timeval current_time)
{
	int current_ms;

	current_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return current_ms;
}
