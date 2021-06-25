/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:32:18 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/25 14:04:14 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int error_handling(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (ft_isdigit(argv[i]) == 1)
            return (1);
        i += 1;
    }
    return (0);
}

void parse_args(int argc, char **argv, t_args *args)
{
    args->number_of_philosophers = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

void initialize_struct(t_args *args)
{
    args->number_of_philosophers = 0;
    args->number_of_times_each_philosopher_must_eat = 0;
    args->time_to_die = 0;
    args->time_to_eat = 0;
    args->time_to_sleep = 0;
    args->isalive = 0;
    args->who_died = 0;
}

int main(int argc, char **argv)
{
    int ret;
    t_args *args;

    ret = 0;
    if (argc == 5 || argc == 6)
    {
        ret = error_handling(argc, argv);
        if (ret == 1)
        {
            write(2, "Bad Arguments !!\n", 17);
            return (1);
        }
        else
        {
            args = malloc(sizeof(t_args));
            initialize_struct(args);
            parse_args(argc, argv, args);
            simulation(args);
        }
    }
    else
        write(2, "Bad Arguments !!\n", 17);
    return (0);
}