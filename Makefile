# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/23 12:33:21 by mlasrite          #+#    #+#              #
#    Updated: 2021/06/24 18:17:09 by mlasrite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c utils.c simulation.c

FLAGE= -Wall -Wextra -Werror 

NAME = philo

all : $(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGE) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
fclean :
	rm -rf $(NAME)
re : clean all