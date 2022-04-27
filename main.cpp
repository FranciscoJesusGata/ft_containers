/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:04 by fgata-va          #+#    #+#             */
/*   Updated: 2022/04/27 15:48:32 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	namespace ft = std;
#else
	#include <vector.hpp>
#endif

int main(void) {
	ft::vector<int> empty;
	ft::vector<int> stuff(5, 100);
}
