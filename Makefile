# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 12:07:26 by fgata-va          #+#    #+#              #
#    Updated: 2023/02/28 18:07:59 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTS := main.cpp test_utils.cpp test_vector.cpp test_stack.cpp test_map.cpp subject_test.cpp

BONUS := test_set.cpp

SRC := $(addprefix tests/, $(TESTS))

BONUS_SRC := $(addprefix tests/, $(BONUS))

CXX := clang++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -I. -Itests/

NAME := test

all: std_$(NAME) ft_$(NAME)

bonus: ft_$(NAME)_bonus std_$(NAME)_bonus

debug:
	$(CXX) $(CXXFLAGS) -g3  $(SRC) -o ft_$(NAME)
	$(CXX) $(CXXFLAGS) -g3  $(SRC) -o std_$(NAME)

ft_$(NAME):
	$(CXX) $(CXXFLAGS) -O3 $(SRC) -o ft_$(NAME)

ft_$(NAME)_bonus:
	$(CXX) $(CXXFLAGS) -O3 -DBONUS $(SRC) $(BONUS_SRC) -o ft_$(NAME)

std_$(NAME):
	$(CXX) $(CXXFLAGS) -O3 -DSTL $(SRC) -o std_$(NAME)

std_$(NAME)_bonus:
	$(CXX) $(CXXFLAGS) -O3 -DBONUS -DSTL $(SRC) $(BONUS_SRC) -o std_$(NAME)

fclean:
	rm -rf ft_$(NAME)* std_$(NAME)*

re: fclean all
