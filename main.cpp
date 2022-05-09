/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:04 by fgata-va          #+#    #+#             */
/*   Updated: 2022/05/09 16:29:00 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	namespace ft = std;
#else
	#include <vector.hpp>
#endif
#include <iostream>
#include <string>

template <class T>
void vector_cmp(ft::vector<T>& v1, ft::vector<T>& v2, std::string errmsg, std::string successmsg) {
	if (v1.size() != v2.size() || v1.capacity() != v2.capacity() || v1 != v2 )
		std::cout << errmsg << " ";
	else
		std::cout << successmsg << " ";
}

template <class T>
void vector_cmp(ft::vector<T> const &v1, ft::vector<T> const &v2, std::string errmsg, std::string successmsg) {
	if (v1.size() != v2.size() || v1.capacity() != v2.capacity() || v1 != v2 )
		std::cout << errmsg << " ";
	else
		std::cout << successmsg << " ";
}

template <class T>
void vector_cmp(ft::vector<T> const &v1, T *v2, size_t len, std::string errmsg, std::string successmsg) {
	if (len != v1.size()) {
		std::cout << errmsg << " ";
		return ;
	}
	for (size_t i = 0; i < v1.size(); i++) {
		if (v1[i] != v2[i]) {
			std::cout << errmsg << " ";
			return ;
		}
	}
	std::cout << successmsg << " ";
}

template <class T>
void	resize_test(ft::vector<T> &v, size_t size, size_t capacity) {
	try {
		v.resize(size);
		if (v.size() != size || v.capacity() != capacity)
			std::cout << "KO Yours: [" << v.size() << "," << v.capacity() << "] Expected: [" << size << "," << capacity << "] ";
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
		if (v.size() != size || v.capacity() != capacity)
			std::cout << "KO Yours: [" << v.size() << "," << v.capacity() << "] Expected: [" << size << "," << capacity << "] ";
		else {
			for (size_t n = original_size; n < size ; n++) {
				if (v[n] != val) {
					std::cout << "KO: Value doesn't match: v[" << n << "] = " << v[n] << std::endl;
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
			std::cout << "KO Yours: [" << v.size() << "," << v.capacity() << "] Expected: [" << old_size << "," << capacity << "] ";
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
			std::cout << "KO: At returns element in a wrong position";
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
			std::cout << "KO: At returns element in a wrong position";
	} catch (std::exception &e) {
		std::cout << e.what() << " ";
	}
}

template <class T>
void	print_vector(ft::vector<T> &v) {
	typename ft::vector<T>::iterator it = v.begin();
	typename ft::vector<T>::iterator end = v.end();

	std::cout << "[ ";
	while (it != end) {
		std::cout << *it++;
		if (it < end)
			std::cout << ", ";
	}
	std::cout << " ]" << std::endl;
}

int main(void) {
	ft::vector<int> empty;
	ft::vector<int> stuff(5, 100);
	ft::vector<int> const cpy(stuff);
	int arr[] = {1, 2, 3, 4, 5};
	ft::vector<int> other_cpy(arr, arr + sizeof(arr) / sizeof(int));

	std::cout << "Constructors tests:" << std::endl;
	vector_cmp<int>(stuff, cpy, "Copy constructor failed", "OK!");
	vector_cmp<int>(other_cpy, arr, sizeof(arr)/sizeof(int), "Iterator constructor failed", "OK!");
	std::cout << (empty.empty() ? "OK! " : "Empty constructor failed ");
	empty = stuff;
	vector_cmp<int>(other_cpy, arr, sizeof(arr)/sizeof(int), "Assignment operator failed", "OK!");
	std::cout << std::endl << std::endl << "Capacity functions tests:" << std::endl;
	std::cout << "Max size: " << empty.max_size() << std::endl;
	std::cout << "Resize:" << std::endl;
	resize_test(empty, 2, empty.capacity());
	resize_test(empty, 10, 10, 42);
	resize_test(empty, 10, empty.capacity(), 0);
	resize_test(empty, 0, empty.capacity());
	resize_test(empty, -10, empty.capacity());
	resize_test(empty, empty.max_size(), empty.max_size());
	std::cout << std::endl << "Reserve:" << std::endl;
	reserve_test(empty, 0);
	reserve_test(empty, 10);
	reserve_test(empty, 20);
	reserve_test(empty, empty.max_size());
	reserve_test(empty, -1);
	std::cout << std::endl << std::endl << "Element access functions tests:" << std::endl;
	std::cout << "At:" << std::endl;
	at_test(empty, 0);
	at_test(empty, 1);
	at_test(cpy, 0);
	at_test(cpy, cpy.size() - 1);
	at_test(cpy, cpy.size());
	at_test(cpy, -1);
	std::cout << std::endl << "Back and Front:" << std::endl;
	std::cout << (stuff[0] == stuff.front() ? "OK! " : "KO Front function doesn't return first element ");
	std::cout << (stuff[stuff.size() - 1] == stuff.back() ? "OK! " : "KO Back function doesn't return last element");
	print_vector(stuff);
	std::cout << std::boolalpha;
	std::cout << (stuff == cpy) << std::endl;
	std::cout << (stuff <= cpy) << std::endl;
	std::cout << std::noboolalpha;
	std::cout << std::endl;
}
