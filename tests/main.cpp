/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:04 by fgata-va          #+#    #+#             */
/*   Updated: 2023/01/16 19:16:25 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tester.hpp>

int	main(int argc, char **argv) {
	argc++; argc--;
	test_vector();
	test_stack();
//	test_map();
//	subject_test();
	system((std::string("leaks -q ") += argv[0] + 2).c_str());
	std::cout << std::endl;
}
