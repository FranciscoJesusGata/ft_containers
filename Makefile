# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 12:07:26 by fgata-va          #+#    #+#              #
#    Updated: 2022/05/25 19:51:52 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := main.cpp

CXX := c++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -I. -g

NAME := test

all: std_$(NAME) ft_$(NAME)

ft_$(NAME):
	$(CXX) $(CXXFLAGS) $(SRC) -o ft_$(NAME)

std_$(NAME):
	$(CXX) $(CXXFLAGS) -DSTD $(SRC) -o std_$(NAME)

fclean:
	rm -rf ft_$(NAME)* std_$(NAME)*

re: fclean all
