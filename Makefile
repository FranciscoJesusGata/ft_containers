# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 12:07:26 by fgata-va          #+#    #+#              #
#    Updated: 2022/09/09 15:00:51 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := main.cpp test_vector.cpp test_map.cpp

CXX := clang++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -I. -g

NAME := test

all: std_$(NAME) ft_$(NAME) rbtree

ft_$(NAME):
	$(CXX) $(CXXFLAGS) $(SRC) -o ft_$(NAME)

std_$(NAME):
	$(CXX) $(CXXFLAGS) -DSTD $(SRC) -o std_$(NAME)

rbtree:
	$(CXX) $(CXXFLAGS) test_rbtree.cpp -o rbtree

fclean:
	rm -rf ft_$(NAME)* std_$(NAME)* rbtree rbtree.dSYM

re: fclean all
