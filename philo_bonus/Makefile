# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/23 12:33:21 by mlasrite          #+#    #+#              #
#    Updated: 2021/06/28 14:25:43 by mlasrite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c utils.c simulation.c status.c sleep.c routine.c supervisord.c

FLAGE= -Wall -Wextra -Werror

NAME = philo_bonus

all : $(NAME)

$(NAME) : $(SRC)
	gcc  $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
fclean :
	rm -rf $(NAME)
re : clean all  