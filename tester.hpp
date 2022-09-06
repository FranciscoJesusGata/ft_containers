/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:41:06 by fgata-va          #+#    #+#             */
/*   Updated: 2022/09/06 17:46:16 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP
# ifdef STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	#include <map>
	namespace ft = std;
# else
	#include <vector.hpp>
	#include <map.hpp>
# endif
# include <iostream>
# include <string>
# include <exception>

void	test_vector(void);
void	test_map(void);
#endif