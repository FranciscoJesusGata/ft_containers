# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 20:11:37 by fgata-va          #+#    #+#              #
#    Updated: 2023/03/03 19:07:26 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make bonus
if [ $? -eq '0' ]; then
	./ft_bonus > ._mine
	./std_bonus > ._standard
	diff -y --suppress-common-lines ._mine ._standard
	rm -rf ._mine ._standard
	make fclean
fi
