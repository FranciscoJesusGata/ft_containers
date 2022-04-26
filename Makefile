# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 12:07:26 by fgata-va          #+#    #+#              #
#    Updated: 2022/04/26 15:18:52 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := main.cpp

CXX := clang++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -I.

NAME := test

all: std_$(NAME) ft_$(NAME)

ft_$(NAME):
	$(CXX) $(CXXFLAGS) $(SRC) -o ft_$(NAME)

std_$(NAME):
	$(CXX) $(CXXFLAGS) -DSTD $(SRC) -o std_$(NAME)

fclean:
	rm -rf ft_$(NAME) std_$(NAME)

re: fclean all
