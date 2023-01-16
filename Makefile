# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 12:07:26 by fgata-va          #+#    #+#              #
#    Updated: 2023/01/12 20:33:49 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTS := main.cpp test_vector.cpp test_stack.cpp test_map.cpp subject_test.cpp

SRC := $(addprefix tests/, $(TESTS))

CXX := clang++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -I. -Itests/

NAME := test

all: std_$(NAME) ft_$(NAME) rbtree

debug:
	$(CXX) $(CXXFLAGS) -g $(SRC) -o ft_$(NAME)

ft_$(NAME):
	$(CXX) $(CXXFLAGS) -O3 $(SRC) -o ft_$(NAME)

std_$(NAME):
	$(CXX) $(CXXFLAGS) -O3 -DSTD $(SRC) -o std_$(NAME)

rbtree:
	$(CXX) $(CXXFLAGS) tests/test_rbtree.cpp -o rbtree

fclean:
	rm -rf ft_$(NAME)* std_$(NAME)* rbtree rbtree.dSYM

re: fclean all
