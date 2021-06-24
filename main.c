/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:32:18 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/24 10:20:52 by mlasrite         ###   ########.fr       */
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

void parse_args(int argc, char **argv, t_args *head)
{
    head->number_of_philosophers = ft_atoi(argv[1]);
    head->time_to_die = ft_atoi(argv[2]);
    head->time_to_eat = ft_atoi(argv[3]);
    head->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        head->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

void initialize_struct(t_args *head)
{
    head->number_of_philosophers = 0;
    head->number_of_times_each_philosopher_must_eat = 0;
    head->time_to_die = 0;
    head->time_to_eat = 0;
    head->time_to_sleep = 0;
}

int main(int argc, char **argv)
{
    int ret;
    t_args *head;

    ret = 0;
    head = (t_args *)malloc(sizeof(t_args));
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
            initialize_struct(head);
            parse_args(argc, argv, head);
            print_struct(head);
        }
    }
    else
        write(2, "Bad Arguments !!\n", 17);
    return (0);
}
