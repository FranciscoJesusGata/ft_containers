/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:50:24 by fgata-va          #+#    #+#             */
/*   Updated: 2023/02/26 20:07:06 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tester.hpp>

void print_timediff(timeval start)
{
	timeval end;
	gettimeofday(&end, NULL);
	double diff = ((static_cast<double>(end.tv_sec) * 1000000.0)
			+ static_cast<double>(end.tv_usec))
		- ((static_cast<double>(start.tv_sec) * 1000000.0)
			+ static_cast<double>(start.tv_usec));
	std::cout << "map: " << std::fixed << std::setprecision(2) << diff << " ms" << std::endl;
}
