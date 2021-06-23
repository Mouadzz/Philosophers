/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:32:18 by mlasrite          #+#    #+#             */
/*   Updated: 2021/06/23 14:04:54 by mlasrite         ###   ########.fr       */
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

int main(int argc, char **argv)
{
    int ret;

    ret = 0;
    if (argc == 5 || argc == 6)
    {
        ret = error_handling(argc, argv);
        if (ret == 1)
        {
            write(2, "Bad Arguments !!\n", 17);
            return (1);
        }
    }
    else
        write(2, "Bad Arguments !!\n", 17);
    return (0);
}
