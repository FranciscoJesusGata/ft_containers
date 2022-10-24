/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:44:15 by fgata-va          #+#    #+#             */
/*   Updated: 2022/09/06 18:19:18 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tester.hpp>
#include <list>

template <class T>
void vector_cmp(ft::vector<T> const &v1, ft::vector<T> const &v2) {
	if (v1 != v2)
		std::cout << "KO💥" << std::endl;
	else
		std::cout << "OK!" << std::endl;
}

template <class T>
void test_cmp(ft::vector<T> const &v1, ft::vector<T> const &v2) {
	std::cout << std::boolalpha;	
	std::cout << "\tv1 == v2 " << (v1 == v2) << std::endl;
	std::cout << "\tv1 != v2 " << (v1 != v2) << std::endl;
	std::cout << "\tv1 < v2 " << (v1 < v2) << std::endl;
	std::cout << "\tv1 <= v2 " << (v1 <= v2) << std::endl;
	std::cout << "\tv1 > v2 " << (v1 > v2) << std::endl;
	std::cout << "\tv1 >= v2 " << (v1 >= v2) << std::endl;
	std::cout << std::noboolalpha;
	std::cout << std::endl;
}

template <class T>
void	fill_const_test(ft::vector<T> const &v, size_t size, T val)
{
	if (v.size() != size) {
		std::cout << "KO💥: Expected size " << size << " ";
		return ;
	}
	for (size_t i = 0; i < size;i++) {
		if (v[i] != val) {
			std::cout << "KO💥: Value doesn't match: v[" << val << "] = " << v[i] << " ";
			return ;
		}
	}
	std::cout << "OK! ";
}

template <class T>
void	resize_test(ft::vector<T> &v, size_t size, size_t capacity) {
	try {
		v.resize(size);
		if (v.size() != size || v.capacity() < capacity)
			std::cout << "KO💥 Yours: [" << v.size() << "," << v.capacity() << "] Expected: [" << size << "," << capacity << "] ";
		else
			std::cout << "OK! ";
	} catch (std::exception &e) {
		std::cout << e.what() << " ";
	}
}

template <class T>
void	resize_test(ft::vector<T> &v, size_t size, size_t capacity, T val) {
	try {
		size_t original_size = v.size();
		v.resize(size, val);
		if (v.size() != size || v.capacity() < capacity)
			std::cout << "KO💥 Yours: [" << v.size() << "," << v.capacity() << "] Expected: [" << size << "," << capacity << "] ";
		else {
			for (size_t n = original_size; n < size ; n++) {
				if (v[n] != val) {
					std::cout << "KO💥: Value doesn't match: v[" << n << "] = " << v[n] << " ";
					return ;
				}
			}
			std::cout << "OK! ";
		}
	} catch (std::exception &e) {
		std::cout << e.what() << " ";
	}
}

template <class T>
void	reserve_test(ft::vector<T> &v, size_t capacity) {
	try {
		size_t old_size = v.size();
		v.reserve(capacity);
		if ((v.capacity() < capacity && v.capacity() != capacity) || v.size() != old_size)
			std::cout << "KO💥 Yours: [" << v.size() << "," << v.capacity() << "] Expected: [" << old_size << "," << capacity << "] ";
		else
			std::cout << "OK! ";
	} catch (std::exception &e) {
		std::cout << e.what() << " ";
	}
}

template <class T>
void	at_test(ft::vector<T> &v, size_t position) {
	try {
		T const &element = v.at(position);
		if (element == v[position])
			std::cout << "OK! ";
		else
			std::cout << "KO💥: At returns element in a wrong position ";
	} catch (std::exception &e) {
		std::cout << e.what() << " ";
	}
}

template <class T>
void	at_test(ft::vector<T> const &v, size_t position) {
	try {
		T const &element = v.at(position);
		if (element == v[position])
			std::cout << "OK! ";
		else
			std::cout << "KO💥: At returns element in a wrong position ";
	} catch (std::exception &e) {
		std::cout << e.what() << " ";
	}
}

template <class T>
void	print_vector(ft::vector<T> &v) {
	std::cout << "[ ";
	for (typename ft::vector<T>::iterator it = v.begin(), end = v.end(); it != end; it++) {
		std::cout << *it;
		if (it + 1 != end)
			std::cout << ", ";
	}
	std::cout << " ]" << std::endl;
}

template <class T>
void	rev_print_vector(ft::vector<T> &v) {
	std::cout << "[ ";
	for (typename ft::vector<T>::reverse_iterator it = v.rbegin(), end = v.rend(); it != end; it++) {
		std::cout << *it;
		if (it + 1 != end)
			std::cout << ", ";
	}
	std::cout << " ]" << std::endl;
}

template <class T>
void	print_vector_ln(ft::vector<T> &v) {
	for (typename ft::vector<T>::iterator it = v.begin(), end = v.end(); it != end; it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
}

template <class T>
void	rev_print_vector_ln(ft::vector<T> &v) {
	for (typename ft::vector<T>::reverse_iterator it = v.rbegin(), end = v.rend(); it != end; it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
}

void	test_vector(void) {
	ft::vector<int>	v;
	std::cout << std::endl << "Capacity functions tests:" << std::endl;
	std::cout << "\tMax size: " << v.max_size() << std::endl;
	std::cout << "\tResize: ";
	resize_test(v, 2, v.capacity());
	resize_test(v, 10, 10, 42);
	resize_test(v, 10, v.capacity(), 0);
	resize_test(v, 0, v.capacity());
	resize_test(v, -10, v.capacity());
	resize_test(v, v.max_size(), v.max_size());
	std::cout << std::endl << "\tReserve: ";
	reserve_test(v, 0);
	reserve_test(v, 10);
	reserve_test(v, 20);
	reserve_test(v, 42);
	reserve_test(v, v.max_size());
	reserve_test(v, -1);
	std::cout << std::endl << std::endl << "Constructors tests:" << std::endl;
	std::cout << "\tFill constructor:";
	ft::vector<int> stuff(5, 100);
	fill_const_test(stuff, 5, 100);
	ft::vector<int> more_stuff(10, 42);
	fill_const_test(more_stuff, 10, 42);
	ft::vector<int> empty;

	std::cout << std::endl << "\tCopy constructor: ";
	ft::vector<int> cpy(stuff);
	vector_cmp<int>(stuff, cpy);

	std::cout << "\tRange constructor:" << std::endl;
	std::list<std::string> src;
	for (size_t i = 0 ; i < 20 ; i++)
		src.push_back(std::string((i % 3) + 1, i + 'a'));
	ft::vector<std::string>range(src.begin(), src.end());
	std::cout << "\t";
	print_vector(range);
	std::cout << "\t";
	rev_print_vector(range);

	std::cout << "\tEmpty constructor: ";
	std::cout << (empty.empty() && empty.size() == 0 && empty.capacity() == 0 ? "OK!" : "KO💥") << std::endl;

	std::cout << "\tAssignment operator: ";
	empty = stuff;
	vector_cmp<int>(empty, stuff);
	ft::vector<int> ft(42,42);
	std::cout << "\t\tBefore: ";
	print_vector(ft);
	ft = stuff;
	std::cout << "\t\tAfter: ";
	print_vector(ft);

	std::cout << "Relational operators tests: " << std::endl;
	test_cmp(ft, stuff);
	ft.resize(10);
	test_cmp(ft, stuff);
	ft.resize(5);
	stuff[0] = 42;
	test_cmp(ft, stuff);
	ft.swap(stuff);
	test_cmp(ft, stuff);
	std::cout << std::endl << std::endl << "Element access functions tests:" << std::endl;
	std::cout << "\tAt: ";
	at_test(empty, 0);
	at_test(empty, 1);
	at_test(range, 0);
	at_test(range, range.size() - 1);
	at_test(range, range.size());
	at_test(range, -1);
	std::cout << std::endl << "\tBack and Front: ";
	std::cout << (stuff[0] == stuff.front() ? "OK! " : "KO Front function doesn't return first element ");
	std::cout << (stuff[stuff.size() - 1] == stuff.back() ? "OK! " : "KO Back function doesn't return last element");
	std::cout << std::endl << "\tBrackets operator: " << std::endl;
	std::cout << "\tvector[0]: " << ft[0] << std::endl;
	std::cout << "\tvector[-1]: " << ft[-1] << std::endl;

	std::cout << std::endl << std::endl << "Modifiers functions tests:" << std::endl;
	std::cout << "\tAssign: " << std::endl;
	std::cout << "\t\tBefore assign: ";
	print_vector(empty);
	empty.assign(10, 21);
	std::cout << "\t\tAfter assign: ";
	print_vector(empty);
	std::cout << std::endl << "\tSwap: " << std::endl;
	std::cout << "\t\tBefore swap: " << std::endl;
	std::cout << "\tV1: ";
	print_vector(empty);
	std::cout << "\tV2: ";
	print_vector(stuff);
	empty.swap(stuff);
	std::cout << "\t\tAfter swap: " << std::endl;
	std::cout << "\tV1: ";
	print_vector(empty);
	std::cout << "\tV2: ";
	print_vector(stuff);
	std::cout << std::endl << "\tClear: " << std::endl;
	std::cout << "\t\tBefore clear: ";
	std::cout << "V: ";
	print_vector(empty);
	std::cout << "\t\tempty: " << std::boolalpha << empty.empty() << std::noboolalpha << std::endl;
	empty.clear();
	std::cout << "\t\tAfter clear: ";
	std::cout << "V: ";
	print_vector(empty);
	std::cout << "\t\tempty: " << std::boolalpha << empty.empty() << std::noboolalpha << std::endl;
	std::cout << "\tInsert:" << std::endl;
	ft::vector<int>	equisde(20);
	ft::vector<int> lol;
	for (size_t i = 0; i < equisde.size() ; i++)
		equisde[i] = (equisde.size() - i) * 3;
	lol.insert(lol.end(), 42);
	lol.insert(lol.begin(), 5, 21);
	print_vector(lol);
	lol.insert(lol.end() - 1, 4);
	print_vector(lol);
	lol.insert(lol.end(), 2, 2);
	print_vector(lol);
	lol.insert(lol.begin() + 2, equisde.begin(), equisde.end());
	equisde.clear();
	print_vector(lol);
	for (int i = 0; i < 10 ; ++i)
		equisde.insert(equisde.end(), i);
	equisde.insert(equisde.begin() + 3, 2, 100);
	print_vector(equisde);
	ft::vector<std::string> abc;
	for (int i = 0; i < 100 ; ++i)
		abc.insert(abc.end(), std::string((i % 3) + 1, (i % 26) + 'a'));
	print_vector(abc);
	abc.insert(abc.begin(), abc.begin(), abc.begin() + 5);
	print_vector(abc);
	std::cout << "\tErase:" << std::endl;
	abc.erase(abc.begin() + 2);
	print_vector(abc);
	abc.erase(abc.begin());
	print_vector(abc);
	abc.erase(abc.end() - 1);
	print_vector(abc);
	abc.erase(abc.begin(), abc.begin() + 4);
	print_vector(abc);
	abc.erase(abc.begin(), abc.begin() + 4);
	print_vector(abc);
	abc.erase(abc.end() - 4, abc.end() - 1);
	print_vector(abc);
	abc.push_back("abc");
	abc.push_back("def");
	abc.push_back("ghi");
	print_vector(abc);
	abc.erase(abc.end() - 4, abc.end() - 1);
	print_vector(abc);
	abc.push_back("LET'S");
	abc.push_back("ALL");
	abc.push_back("LOVE");
	abc.push_back("LAIN");
	print_vector(abc);
	abc.erase(abc.begin(), abc.end());
	print_vector(abc);
}
