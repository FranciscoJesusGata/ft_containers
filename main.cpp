/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:04 by fgata-va          #+#    #+#             */
/*   Updated: 2022/04/29 17:26:57 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	namespace ft = std;
#else
	#include <vector.hpp>
#endif
#include <iostream>

int main(void) {
	ft::vector<int> empty;
	ft::vector<int> stuff(5, 100);
	ft::vector<int> cpy(stuff);

	std::cout << std::boolalpha;
	std::cout << empty.empty() << std::endl;
	std::cout << std::noboolalpha;
	empty = stuff;
	std::cout << empty.size() << std::endl;
	std::cout << empty.capacity() << std::endl;
	empty.resize(2);
	std::cout << empty.size() << std::endl;
	std::cout << empty.capacity() << std::endl;
	empty.resize(10);
	std::cout << empty.size() << std::endl;
	std::cout << empty.capacity() << std::endl;
	empty.resize(0);
	std::cout << empty.size() << std::endl;
	std::cout << empty.capacity() << std::endl;
	try {
		empty.resize(-10);
		std::cout << empty.size() << std::endl;
		std::cout << empty.capacity() << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << stuff[4] << std::endl;
	std::cout << empty[4] << std::endl;
	try {
		std::cout << empty.at(4) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
