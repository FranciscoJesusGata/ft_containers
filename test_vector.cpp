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

template <class T>
void vector_cmp(ft::vector<T>& v1, ft::vector<T>& v2, std::string errmsg, std::string successmsg) {
	if (v1.size() != v2.size() || v1.capacity() != v2.capacity() || v1 != v2 )
		std::cout << errmsg << " ";
	else
		std::cout << successmsg << " ";
}

template <class T>
void vector_cmp(ft::vector<T> const &v1, ft::vector<T> const &v2) {
	if (v1.size() != v2.size() || v1.capacity() != v2.capacity() || v1 != v2 )
		std::cout << "KO💥" << std::endl;
	else
		std::cout << "OK!" << std::endl;
}

template <class T>
void vector_cmp(ft::vector<T> const &v1, T *v2, size_t len) {
	if (len != v1.size()) {
		std::cout << "KO💥" << std::endl;
		return ;
	}
	for (size_t i = 0; i < v1.size(); i++) {
		if (v1[i] != v2[i]) {
			std::cout << "KO💥" << std::endl;
			return ;
		}
	}
	std::cout << "OK!" << std::endl;
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

void	test_vector(void) {
	ft::vector<int> empty;
	ft::vector<int> stuff(5, 100);
	ft::vector<int> const cpy(stuff);
	int arr[] = {1, 2, 3, 4, 5};
	ft::vector<int> other_cpy(arr, arr + sizeof(arr) / sizeof(int));

	std::cout << "Constructors tests:" << std::endl;
	std::cout << "\tCopy constructor: ";
	vector_cmp<int>(stuff, cpy);
	std::cout << "\tIterator constructor: ";
	vector_cmp<int>(other_cpy, arr, sizeof(arr)/sizeof(int));
	std::cout << "\tEmpty constructor: ";
	std::cout << (empty.empty() ? "OK!" : "KO💥") << std::endl;
	std::cout << "\tAssignment operator: ";
	empty = stuff;
	vector_cmp<int>(other_cpy, arr, sizeof(arr)/sizeof(int));
	std::cout << std::endl << "Capacity functions tests:" << std::endl;
	std::cout << "\tMax size: " << empty.max_size() << std::endl;
	std::cout << "\tResize: ";
	resize_test(empty, 2, empty.capacity());
	resize_test(empty, 10, 10, 42);
	resize_test(empty, 10, empty.capacity(), 0);
	resize_test(empty, 0, empty.capacity());
	resize_test(empty, -10, empty.capacity());
	resize_test(empty, empty.max_size(), empty.max_size());
	std::cout << std::endl << "\tReserve: ";
	reserve_test(empty, 0);
	reserve_test(empty, 10);
	reserve_test(empty, 20);
	reserve_test(empty, empty.max_size());
	reserve_test(empty, -1);
	std::cout << std::endl << std::endl << "Element access functions tests:" << std::endl;
	std::cout << "\tAt: ";
	at_test(empty, 0);
	at_test(empty, 1);
	at_test(cpy, 0);
	at_test(cpy, cpy.size() - 1);
	at_test(cpy, cpy.size());
	at_test(cpy, -1);
	std::cout << std::endl << "\tBack and Front: ";
	std::cout << (stuff[0] == stuff.front() ? "OK! " : "KO Front function doesn't return first element ");
	std::cout << (stuff[stuff.size() - 1] == stuff.back() ? "OK! " : "KO Back function doesn't return last element");
	std::cout << (stuff == cpy ? "OK! " : "KO💥 ") << " ";
	std::cout << (stuff <= cpy ? "OK! " : "KO💥 ") << std::endl;
	empty.assign(10, 42);
	print_vector(empty);
	empty.insert(empty.begin() + 4, 21);
	print_vector(empty);
	stuff.insert(stuff.begin(), 101);
	print_vector(stuff);
	other_cpy.insert(other_cpy.begin() + 2, 42);
	print_vector(other_cpy);
	stuff.insert(stuff.begin(), 5, 98);
	print_vector(stuff);
	stuff.insert(stuff.begin(), 9, 84);
	print_vector(stuff);
	empty.insert(empty.begin(), stuff.begin(), stuff.begin() + 9);
	print_vector(empty);

	ft::vector<int> defaut_vct;
	defaut_vct.insert(defaut_vct.begin(), 5, 42);
	print_vector(defaut_vct);
}