# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 20:11:37 by fgata-va          #+#    #+#              #
#    Updated: 2022/09/06 20:18:56 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make re
if [ $? -eq '0' ]; then
	./ft_test > _mine
	./std_test > _standard
	diff -y --suppress-common-lines _mine _standard
	rm -rf ft_test std_test _mine _standard
fi