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
	#include <stack>
	#include <map>
	namespace ft = std;
# else
	#include <vector.hpp>
	#include <stack.hpp>
	#include <map.hpp>
# endif
# include <iostream>
# include <string>
# include <exception>
# include <cstdlib>
# include <ctime>
# include <deque>
//Subject test stuff
# define MAX_RAM 4294967296
# define BUFFER_SIZE 4096
# define COUNT (MAX_RAM / (int)sizeof(Buffer))

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

void	test_vector(void);
void	test_map(void);
void	subject_test(void);

#endif
