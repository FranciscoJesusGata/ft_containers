/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:04 by fgata-va          #+#    #+#             */
/*   Updated: 2022/09/06 17:46:24 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tester.hpp>

int	main(int argc, char **argv) {
	argc++; argc--;
	test_vector();
//	test_map();
//	subject_test();
	system((std::string("leaks -q ") += argv[0] + 2).c_str());
	std::cout << std::endl;
}
