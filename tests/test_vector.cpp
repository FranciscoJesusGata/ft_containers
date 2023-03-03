/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:44:15 by fgata-va          #+#    #+#             */
/*   Updated: 2023/03/03 18:55:41 by fgata-va         ###   ########.fr       */
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
	std::cout << "Size:" << v.size() << " ";
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
	std::cout << "Size:" << v.size() << " ";
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
	std::cout << "Size:" << v.size() << std::endl;
	for (typename ft::vector<T>::iterator it = v.begin(), end = v.end(); it != end; it++)
		std::cout << "| " << *it << std::endl;
	std::cout << std::endl;
}

template <class T>
void	rev_print_vector_ln(ft::vector<T> &v) {
	std::cout << "Size:" << v.size() << std::endl;
	for (typename ft::vector<T>::reverse_iterator it = v.rbegin(), end = v.rend(); it != end; it++)
		std::cout << "| " << *it << std::endl;
	std::cout << std::endl;
}

template <typename It1, typename It2>
void	iterator_rel_op_tests(It1 const &lhs, It2 const &rhs)
{
	std::cout << (lhs == rhs) << std::endl;
	std::cout << (lhs != rhs) << std::endl;
	std::cout << (lhs <= rhs) << std::endl;
	std::cout << (lhs < rhs) << std::endl;
	std::cout << (lhs >= rhs) << std::endl;
	std::cout << (lhs > rhs) << std::endl;
}

void	test_vector(void) {
	timeval start;
	gettimeofday(&start, NULL);
	std::cout << std::endl << "Capacity functions tests:" << std::endl;
	{
		ft::vector<int>	v;
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
	}
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
	std::cout << "\t\tBefore: " << std::endl;
	print_vector(ft);
	ft = stuff;
	std::cout << "\t\tAfter: " << std::endl;
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
	{
		ft::vector<int> const v_const(empty);
		at_test(empty, 0);
		at_test(empty, 1);
		at_test(range, 0);
		for (size_t i = 0; i < v_const.size() ; i++)
			at_test(v_const, i);
		at_test(range, range.size() - 1);
		at_test(range, range.size());
		at_test(range, -1);
	}
	std::cout << std::endl << "\tBack and Front: ";
	std::cout << (stuff[0] == stuff.front() ? "OK! " : "KO Front function doesn't return first element ");
	std::cout << (stuff[stuff.size() - 1] == stuff.back() ? "OK! " : "KO Back function doesn't return last element");
	std::cout << std::endl << "\tBrackets operator: " << std::endl;
	std::cout << "\tvector[0]: " << ft[0] << std::endl;
	std::cout << "\tvector[-1]: " << ft[-1] << std::endl;

	std::cout << std::endl << std::endl << "Modifiers functions tests:" << std::endl;
	std::cout << "\tAssign: " << std::endl;
	{
		ft::vector<int>	first(10);
		ft::vector<int> second(5);
		ft::vector<int> third;
		ft::vector<int> forth;
		for (size_t i = 0; i < first.size() ; i++)
			first[i] = first.size() - i - 1;
		for (size_t i = 0; i < second.size() ; i++)
			second[i] = (i + 1) * 5;
		std::cout << "\t\tBefore assign: " << std::endl;
		print_vector(first);
		print_vector(second);
		third.assign(first.begin(), first.end());
		forth.assign(third.begin(), third.end() - 5);
		first.assign(5, 21);
		second.assign(2, 42);
		std::cout << "\t\tAfter assign: " << std::endl;
		print_vector(first);
		print_vector(second);
		print_vector(third);
		print_vector(forth);
	}
	std::cout << std::endl << "\tPush back and pop back: " << std::endl;
	{
		ft::vector<std::string> toSmart;
		ft::vector<std::string> tooProgramCpp(10);

		for (size_t i = 0 ; i < 10 ; i++)
			tooProgramCpp[i] = std::string(i + 1, i + 65);
		print_vector(tooProgramCpp);
		for (int i = tooProgramCpp.size() - 1 ; i >= 0 ; i--)
			toSmart.push_back(tooProgramCpp[i]);
		print_vector(toSmart);
		toSmart.push_back("Sigma male based red pilled programer (please help)");
		tooProgramCpp.push_back("I rly am to smart too program in c++ bruh");
		print_vector(toSmart);
		print_vector(tooProgramCpp);
		toSmart.pop_back();
		tooProgramCpp.pop_back();
		print_vector(toSmart);
		print_vector(tooProgramCpp);
	}
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
	print_timediff("vector", start);
	gettimeofday(&start, NULL);
	std::cout << "\tInsert:" << std::endl;
	{
		ft::vector<int>	equisde(20);
		ft::vector<int> lol;
		for (size_t i = 0; i < equisde.size() ; i++)
			equisde[i] = (equisde.size() - i) * 3;
		lol.insert(lol.end(), 42);
		lol.insert(lol.begin(), 5, 21);
		print_vector_ln(lol);
		lol.insert(lol.end() - 1, 4);
		print_vector_ln(lol);
		lol.insert(lol.end(), 2, 2);
		print_vector_ln(lol);
		lol.insert(lol.begin() + 2, equisde.begin(), equisde.end());
		equisde.clear();
		print_vector_ln(lol);
		for (int i = 0; i < 10 ; ++i)
			equisde.insert(equisde.end(), i);
		equisde.insert(equisde.begin() + 3, 2, 100);
		print_vector_ln(equisde);
	}
	{
		ft::vector<std::string> abc;
		for (int i = 0; i < 100 ; ++i)
			abc.insert(abc.end(), std::string((i % 3) + 1, (i % 26) + 'a'));
		print_vector_ln(abc);
		abc.insert(abc.begin(), abc.begin(), abc.begin() + 5);
		print_vector_ln(abc);
		std::cout << "\tErase:" << std::endl;
		abc.erase(abc.begin() + 2);
		print_vector_ln(abc);
		abc.erase(abc.begin());
		print_vector_ln(abc);
		abc.erase(abc.end() - 1);
		print_vector_ln(abc);
		abc.erase(abc.begin(), abc.begin() + 4);
		print_vector_ln(abc);
		abc.erase(abc.begin(), abc.begin() + 4);
		print_vector_ln(abc);
		abc.erase(abc.end() - 4, abc.end() - 1);
		print_vector_ln(abc);
		abc.push_back("abc");
		abc.push_back("def");
		abc.push_back("ghi");
		print_vector_ln(abc);
		abc.erase(abc.end() - 4, abc.end() - 1);
		print_vector_ln(abc);
		abc.push_back("LET'S");
		abc.push_back("ALL");
		abc.push_back("LOVE");
		abc.push_back("LAIN");
		print_vector_ln(abc);
		abc.erase(abc.end() - 4, abc.end());
		print_vector_ln(abc);
		abc.erase(abc.begin(), abc.end());
		print_vector_ln(abc);
	}
	std::cout << std::endl << std::endl << "Vector iterator tests:" << std::endl;
	{
		ft::vector<std::string> wow;
		for (int i = 0 ; i < 10 ; i++)
			wow.push_back(std::string((i % 3) + 1, i + 'a'));
		ft::vector<std::string>::iterator it = wow.begin();
		ft::vector<std::string>::iterator it2;
		ft::vector<std::string>::const_iterator c_it;
		
		std::cout << "\tPre and post incremend and decrement: " << std::endl;
		std::cout << "\t\tPreincrement" << std::endl;
		it2 = ++it;
		std::cout << "\t\t" << *it << " " << *it2 << std::endl;
		std::cout << "\t\tPosincrement" << std::endl;
		it2 = it++;
		std::cout  << "\t\t" << *it << " " << *it2 << std::endl;
		std::cout << "\t\tPredecrement" << std::endl;
		it2 = --it;
		std::cout  << "\t\t" << *it << " " << *it2 << std::endl;
		std::cout << "\t\tPosdecrement" << std::endl;
		it2 = it--;
		std::cout  << "\t\t" << *it << " " << *it2 << std::endl;
		
		std::cout << "\tIncrement, decrement and assing operators:" << std::endl;
		it = it + 4;
		it = 2 + it;
		it  = it - 4;
		std::cout << "\t\t"  << *it << std::endl;
		std::cout << "\t\t" << *(it += 4) << std::endl;
		std::cout << "\t\t" << *(it += 2) << std::endl;
		*(it -= 2) = "🌯";
		*(it += 2) = "👀";	
		it -= 4;
		c_it = it;
		std::cout << "\t\t" << *(c_it += 4) << std::endl;
		std::cout << "\t\t" << *(c_it -= 2) << std::endl;
		std::cout << std::boolalpha;
		std::cout << "\t\titerator == const iterator " << (c_it == it) << std::endl;
		std::cout << std::noboolalpha;
		std::cout << "\t\titerator - const iterator " << (it - c_it) << std::endl;
		std::cout << "\t\tconst iterator - iterator " << (c_it - it) << std::endl;
		std::cout << "\t\tconst iterator + 3 - iterator " << (c_it + 3 - it) << std::endl;
		std::cout << "\t\titerator + 2 - const iterator " << (it + 2 - c_it) << std::endl;
	}
	{
		std::cout << "\tDereference operators:" << std::endl;
		ft::vector<Dummy<int> > dummyVector(10);
		ft::vector<Dummy<int> >::iterator it = dummyVector.begin();
		ft::vector<Dummy<int> >::iterator middle;
		ft::vector<Dummy<int> >::iterator end = dummyVector.end();;
		ft::vector<Dummy<int> >::const_iterator c_it;
		ft::vector<Dummy<int> >::const_iterator c_middle;
		ft::vector<Dummy<int> >::const_iterator c_end;

		for	(int i = 1 ; it != end ; it++) {
			*it = (i + 1) * 2;
			i++;
		}
	
		it = dummyVector.begin();	
		c_it = it;

		std::cout << *(it++) << std::endl;
		std::cout << *(++it) << std::endl;
		std::cout << *(--it) << std::endl;
		std::cout << *(it--) << std::endl;

		std::cout << *(c_it++) << std::endl;
		std::cout << *(++c_it) << std::endl;
		std::cout << *(--c_it) << std::endl;
		std::cout << *(c_it--) << std::endl;
	
		std::cout << *it++ << std::endl;
		std::cout << *++it << std::endl;
		std::cout << *--it << std::endl;
		std::cout << *it-- << std::endl;

		std::cout << *c_it++ << std::endl;
		std::cout << *++c_it << std::endl;
		std::cout << *--c_it << std::endl;
		std::cout << *c_it-- << std::endl;

		it->dummyMethod();
		c_it->dummyMethod();
		(*it).dummyMethod();
		(*c_it).dummyMethod();

		std::cout << "\tRelational operators tests:" << std::endl;
		std::cout << std::boolalpha;
		it = dummyVector.begin();
		c_it = dummyVector.begin();
		middle = it + 5;
		c_middle = middle;		
		end = dummyVector.end();
		c_end = end;
		std::cout << ((it + 5 == c_it + 5) && (c_it + 5 == middle)) << std::endl;
		iterator_rel_op_tests(it, middle);
		iterator_rel_op_tests(it, end);
		iterator_rel_op_tests(c_it, c_middle);
		iterator_rel_op_tests(it, c_end);
		iterator_rel_op_tests(c_it, it);
		iterator_rel_op_tests(c_middle, middle);
		iterator_rel_op_tests(c_end, end);
		iterator_rel_op_tests(c_it, middle);
		iterator_rel_op_tests(c_it, end);
		iterator_rel_op_tests(it, c_middle);
		iterator_rel_op_tests(it, c_end);
	}
	std::cout << std::endl << std::endl << "Vector reverse iterator tests" << std::endl;
	{
		std::cout << "\tBase offset tests:" << std::endl;
		ft::vector<int> reversed_vct(10);
		ft::vector<int>::iterator it(reversed_vct.begin());
		ft::vector<int>::reverse_iterator rit(it);

		for (int i = 10, j = 0; i >= 0 ; i--)
			reversed_vct[j++] = i;
		std::cout << std::boolalpha;
		std::cout << (rit.base() == it) << std::endl;
		std::cout << ((rit - 5).base() == it) << std::endl;
		std::cout << ((rit - 1).base() == it) << std::endl;
		std::cout << *rit.base() << std::endl;
		std::cout << *(rit.base() + 1) << std::endl;
		std::cout << *(rit - 1).base() << std::endl;
		rit -= 5;
		std::cout << *rit << std::endl;
		std::cout << *(rit.base()) << std::endl;

		std::cout << "\tConstant test:" << std::endl;
		ft::vector<int>::reverse_iterator rite(reversed_vct.begin());
		ft::vector<int>::const_reverse_iterator c_rite(reversed_vct.begin());
		
		rite = rite - 7;
		rite = 1 + rite;
		rite = rite + 4;
		std::cout << "\t\t" << *(rite -= 4) << std::endl;
		std::cout << "\t\t" << *(rite += 2) << std::endl;
		*(rite -= 2) = 808;
		*(rite += 2) = 1010;
		std::cout << "\t\t" << *(c_rite -= 4) << " " << *(c_rite += 2) << std::endl;
		std::cout << "\t\t" << (rite == c_rite) << std::endl;
		std::cout << "\t\treverse iterator - const reverse iterator " << (rite - c_rite) << std::endl;
		std::cout << "\t\tconst iterator - iterator " << (c_rite - rite) << std::endl;
		std::cout << "\t\tconst iterator + 3 - iterator " << (c_rite + 1 - rite) << std::endl;
		std::cout << "\t\titerator + 2 - const iterator " << (rite + 2 - c_rite) << std::endl;
		
	}
	{
		std::cout << "\tDereference operators:" << std::endl;
		ft::vector<Dummy<int> > dummyVector(10);
		ft::vector<Dummy<int> >::reverse_iterator it(dummyVector.end());
		ft::vector<Dummy<int> >::reverse_iterator middle(it + 5);
		ft::vector<Dummy<int> >::reverse_iterator end(dummyVector.begin());
		ft::vector<Dummy<int> >::const_reverse_iterator c_it(it);
		ft::vector<Dummy<int> >::const_reverse_iterator c_middle(middle);
		ft::vector<Dummy<int> >::const_reverse_iterator c_end(end);

		for	(int i = 1 ; i <= 10 ; i++) {
			dummyVector[i] = i * 2;
		}
	
		std::cout << *(it++) << std::endl;
		std::cout << *(++it) << std::endl;
		std::cout << *(--it) << std::endl;
		std::cout << *(it--) << std::endl;

		std::cout << *(c_it++) << std::endl;
		std::cout << *(++c_it) << std::endl;
		std::cout << *(--c_it) << std::endl;
		std::cout << *(c_it--) << std::endl;
	
		std::cout << *it++ << std::endl;
		std::cout << *++it << std::endl;
		std::cout << *--it << std::endl;
		std::cout << *it-- << std::endl;

		std::cout << *c_it++ << std::endl;
		std::cout << *++c_it << std::endl;
		std::cout << *--c_it << std::endl;
		std::cout << *c_it-- << std::endl;

		it->dummyMethod();
		c_it->dummyMethod();
		(*it).dummyMethod();
		(*c_it).dummyMethod();

		std::cout << "\tRelational operators tests:" << std::endl;
		std::cout << std::boolalpha;
		std::cout << ((it + 5 == c_it + 5) && (c_it + 5 == middle)) << std::endl;
		iterator_rel_op_tests(it, middle);
		iterator_rel_op_tests(it, end);
		iterator_rel_op_tests(c_it, c_middle);
		iterator_rel_op_tests(it, c_end);
		iterator_rel_op_tests(c_it, it);
		iterator_rel_op_tests(c_middle, middle);
		iterator_rel_op_tests(c_end, end);
		iterator_rel_op_tests(c_it, middle);
		iterator_rel_op_tests(c_it, end);
		iterator_rel_op_tests(it, c_middle);
		iterator_rel_op_tests(it, c_end);
	}
	print_timediff("vector", start);
	std::cout << "Worst case scenarios: " << std::endl;
	{
		gettimeofday(&start, NULL);
		ft::vector<std::string> death;

		for (size_t i = 0; i < 1e6 ; i++)
			death.push_back(std::string((i % 10) + 1, ((i + 1) % 26) + 'A'));
		death.insert(death.end(), "💀");
		death.insert(death.end(), 5, " L M A O ");
		death.insert(death.end(), death.begin(), ++(++(++(++death.begin()))));
		death.erase(death.end() - 1);
		death.erase(death.end() - 10);
		death.erase(death.end() - 20, death.end() - 1);
		death.assign(death.begin(), death.begin() + 10);
		death.assign(20, "AAAAAAAAAAAAAAAH");
	}
	print_timediff("vector", start);
}
