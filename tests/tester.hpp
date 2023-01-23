/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:41:06 by fgata-va          #+#    #+#             */
/*   Updated: 2023/01/23 20:54:12 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP
# ifdef STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	#include <stack>
	#include <map>
	#include <utility>
	namespace ft = std;
# else
	#include <vector.hpp>
	#include <stack.hpp>
	#include <map.hpp>
	#include <utility.hpp>
# endif
# include <iostream>
# include <string>
# include <exception>
# include <cstdlib>
# include <ctime>
# include <deque>
# include <ostream>
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

template <typename T>
class Dummy {
	public:
		typedef T	value_type;

		Dummy(void): item() {}
		Dummy(value_type v): item(v) {}
		Dummy(Dummy const &src): item(src.item) {}
		~Dummy() {}

		Dummy	&operator=(Dummy const &src) {
			if (src != *this)
				item = src.item;
			return (*this);
		}

		Dummy	&operator=(T const &src) {
			item = src;
			return (*this);
		}

		void	dummyMethod(void) {
			std::cout << "This is a Dummy method, this instance have a item with a value of: " << item << std::endl;
		}

		void	dummyMethod(void) const {
			std::cout << "This is a Dummy method, this instance is const and have a item with a value of: " << item << std::endl;
		}

		bool	operator==(Dummy const &rhs) const {
			return (item == rhs.item);
		}
		
		bool	operator!=(Dummy const &rhs) const {
			return (!(*this == rhs));
		}

		T		&operator*(void) {
			return (item);
		}

		T		get_item(void) const {
			return (item);
		}

	private:
		value_type	item;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, const Dummy<T> &rhs) {
	o << rhs.get_item(); 
	return (o);
}

void	test_vector(void);
void	test_stack(void);
void	test_map(void);
void	subject_test(void);

# ifdef BONUS
#  ifdef STD
#   include <set>
#  else 
#   include <set.hpp>
#  endif
void	test_set(void);
# endif

#endif
