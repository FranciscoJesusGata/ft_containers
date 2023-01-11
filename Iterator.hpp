/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:00:59 by fgata-va          #+#    #+#             */
/*   Updated: 2023/01/11 20:46:55 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <type_traits.hpp>
# include <iterator_traits.hpp>
# include <RBTree.hpp>

namespace ft {

	template <class It>
	class	reverse_iterator {
		public:
			typedef It													iterator_type;
			typedef typename ft::iterator_traits<It>::difference_type	difference_type;
			typedef typename ft::iterator_traits<It>::value_type		value_type;
			typedef typename ft::iterator_traits<It>::pointer			pointer;
			typedef typename ft::iterator_traits<It>::reference			reference;
			typedef typename ft::iterator_traits<It>::iterator_category	random_access_iterator_tag;

			reverse_iterator(): _base() {}
			reverse_iterator(iterator_type const &it): _base(it) {--_base;}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) { _base = --rev_it.base(); }

			iterator_type		base() const { return (++iterator_type(_base)); }
			iterator_type		getIterator() const {return (_base); }
			//dereference operators
			reference				operator*() const { return (*(_base)); }
			reference				operator[](difference_type n) const { return (_base[-n]); }
			pointer					operator->() const { return (&(*_base)); }
			//arithmetic operators
			reverse_iterator		operator+(difference_type n) const { return (reverse_iterator(_base - n + 1)); }
			reverse_iterator		operator-(difference_type n) const { return (reverse_iterator(_base + n + 1)); }
			friend reverse_iterator	operator+(difference_type n, reverse_iterator &rhs) { return (rhs + n); }
			friend reverse_iterator	operator-(difference_type n, reverse_iterator &rhs) { return (rhs - n); }
			template <class Iter>
			difference_type			operator+(reverse_iterator<Iter> &rhs) { return (_base + rhs.base() + 1); }
			template <class Iter>
			difference_type			operator-(reverse_iterator<Iter> &rhs) { return (-(_base - rhs.base() + 1)); }
			reverse_iterator		&operator++() {
				--_base;
				return (*this);
			}
			reverse_iterator	operator++(int) {
				reverse_iterator tmp(*this);
				++(*this);
				return (tmp);
			}
			reverse_iterator	&operator--() {
				++_base;
				return (*this);
			}
			reverse_iterator	operator--(int) {
				reverse_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
			reverse_iterator	&operator+=(difference_type n) {
				_base -= n;
				return (*this);
			}
			reverse_iterator	&operator-=(difference_type n) {
				_base += n;
				return (*this);
			}

			template <class Iter>
			bool			operator==(reverse_iterator<Iter> const& lhs) const {
				return (_base == lhs.getIterator());
			}
			template <class Iter>
			bool			operator!=(reverse_iterator<Iter> const& lhs) const {
				return (_base != lhs.getIterator());
			}

			template <class Iter>
			bool			operator<(reverse_iterator<Iter> const& lhs) const {
				return (_base > lhs.getIterator());
			}

			template <class Iter>
			bool			operator>(reverse_iterator<Iter> const& lhs) const {
				return (_base < lhs.getIterator());
			}

			template <class Iter>
			bool			operator<=(reverse_iterator<Iter> const& lhs) const {
				return (_base >= lhs.getIterator());
			}

			template <class Iter>
			bool			operator>=(reverse_iterator<Iter> const& lhs) const {
				return (_base <= lhs.getIterator());
			}

		private:
			iterator_type	_base;
	};

	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator- (
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() - rhs.base());
	}

	template <class T, bool Const>
	class vector_iterator: public std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef typename ft::conditional<Const, const T, T>::type				value_type;
			typedef typename ft::iterator_traits<value_type *>::difference_type		difference_type;
			typedef typename ft::iterator_traits<value_type *>::pointer				pointer;
			typedef typename ft::iterator_traits<value_type *>::reference			reference;
			typedef typename ft::iterator_traits<value_type *>::iterator_category	random_access_iterator_tag;

			vector_iterator(): _pointer(NULL) {}
			vector_iterator(T *src): _pointer(src) {}
			template <bool C> vector_iterator(vector_iterator<T, C> const &src) {_pointer = src.getPointer(); }
			~vector_iterator() {}

			pointer			getPointer() const {
				return (_pointer);
			}

			vector_iterator	&operator=(vector_iterator const & rhs) {
				if (rhs._pointer != this->_pointer)
					this->_pointer = rhs._pointer;
				return (*this);
			}

			vector_iterator	&operator=(T *rhs) {
				if (rhs != this->_pointer)
					this->_pointer = rhs;
				return (*this);
			}

			template <bool C>
			bool			operator<(vector_iterator<T, C> const& rhs) const {
				return (this->_pointer < rhs.getPointer());
			}

			template <bool C>
			bool			operator>(vector_iterator<T, C> const& rhs) const {
				return (rhs < *this);
			}

			template <bool C>
			bool			operator<=(vector_iterator<T, C> const& rhs) const {
				return (this->_pointer <= rhs.getPointer());
			}

			template <bool C>
			bool			operator>=(vector_iterator<T, C> const& rhs) const {
				return (rhs <= *this);
			}

			template <bool C>
			bool			operator==(vector_iterator<T, C> const& rhs) const {
				return (this->_pointer == rhs.getPointer());
			}

			template <bool C>
			bool			operator!=(vector_iterator<T, C> const& rhs) const {
				return (!(*this == rhs));
			}

			reference		operator*() {
				return (*this->_pointer);
			}

			reference		operator*() const {
				return (*this->_pointer);
			}

			pointer		operator->() {
				return (this->_pointer);
			}

			pointer		operator->() const {
				return (this->_pointer);
			}

			vector_iterator	&operator++() {
				++this->_pointer;
				return (*this);
			}

			vector_iterator	operator++(int) {
				vector_iterator	temp(*this);
				++(*this);
				return (temp);
			}

			vector_iterator	&operator--() {
				--this->_pointer;
				return (*this);
			}

			vector_iterator	operator--(int) {
				vector_iterator	temp(*this);
				--this->_pointer;
				return (temp);
			}

			vector_iterator	operator+(int n) const {
				return (this->_pointer + n);
			}

			vector_iterator	operator-(int n) const {
				return (this->_pointer - n);
			}

			template <bool C>
			difference_type	operator+(vector_iterator<T, C> const &lhs) const {
				return (this->_pointer + lhs.getPointer());
			}

			template <bool C>
			difference_type	operator-(vector_iterator<T, C> const &lhs) const {
				return (this->_pointer - lhs.getPointer());
			}

			friend vector_iterator	operator+(int n, vector_iterator const& rhs) {
				return (rhs.getPointer() + n);
			}

			friend vector_iterator	operator-(int n, vector_iterator const& rhs) {
				return (rhs.getPointer() - n);
			}

			vector_iterator	&operator+=(vector_iterator const &lhs) {
				*this = *this + lhs;
				return (*this);
			}

			vector_iterator	&operator-=(vector_iterator const &lhs) {
				*this = *this - lhs;
				return (*this);
			}

			vector_iterator	&operator+=(int n) {
				this->_pointer = this->_pointer + n;
				return (*this);
			}

			vector_iterator	&operator-=(int n) {
				this->_pointer = this->_pointer - n;
				return (*this);
			}

			reference	operator[](size_t n) {
				return (this->_pointer[n]);
			}

			reference	operator[](size_t n) const {
				return (this->_pointer[n]);
			}

		private:
			T*	_pointer;
	};

	template <class T, bool Const>
	class map_iterator: public std::iterator<std::bidirectional_iterator_tag, T> {
		private:
			typedef typename ft::conditional<Const, const ft::RBTreeNode<T>, ft::RBTreeNode<T> >::type									node_type;
			node_type																																																		*_node;

		public:
			typedef	typename ft::conditional<Const, const T, T >::type																	value_type;
			typedef typename ft::iterator_traits<value_type *>::difference_type													difference_type;
			typedef typename ft::iterator_traits<value_type *>::pointer																	pointer;
			typedef typename ft::iterator_traits<value_type *>::reference																reference;
			typedef typename ft::iterator_traits<value_type *>::iterator_category												bidirectional_iterator_tag;

			map_iterator(): _node(NULL) {}
			map_iterator(node_type * const src): _node(src) {}
			template <bool B>
			map_iterator(map_iterator<T, B> const &src): _node(src.getNode()) {}
			~map_iterator() {}

			node_type		*getNode() const {
				return (_node);
			}

			map_iterator	&operator=(map_iterator const &rhs) {
				if (rhs._node != this->_node)
					this->_node = rhs._node;
				return (*this);
			}

			template <bool B>
			bool			operator==(map_iterator<T, B> const& rhs) const {
				return (this->_node == rhs.getNode());
			}

			template <bool B>
			bool			operator!=(map_iterator<T, B> const& rhs) const {
				return (!(*this == rhs));
			}

			reference		operator*() {
				return (this->_node->item);
			}

			reference		operator*() const {
				return (this->_node->item);
			}

			pointer		operator->() {
				return (&this->_node->item);
			}

			pointer		operator->() const {
				return (&this->_node->item);
			}

			map_iterator	&operator++() {
				_node = ft::next_node<T, Const>(_node);
				return (*this);
			}

			map_iterator	operator++(int) {
				map_iterator	temp(*this);
				++(*this);
				return (temp);
			}

			map_iterator	&operator--() {
				_node = ft::prev_node<T, Const>(_node);
				return (*this);
			}

			map_iterator	operator--(int) {
				map_iterator	temp(*this);
				--(*this);
				return (temp);
			}
	};

	template <class T, bool Const>
	class	set_iterator: public std::iterator<std::bidirectional_iterator_tag, T> {
		private:
			typedef typename ft::RBTreeNode<const T>																																node_type;
			node_type																																																*_node;

		public:
			typedef T const																																													value_type;
			typedef typename ft::iterator_traits<value_type*>::difference_type																					difference_type;
			typedef typename ft::iterator_traits<value_type*>::pointer																									pointer;
			typedef typename ft::iterator_traits<value_type*>::reference																								reference;
			typedef typename ft::iterator_traits<value_type*>::iterator_category																				bidirectional_iterator_tag;

			set_iterator(): _node(NULL) {}
			set_iterator(node_type * const src): _node(src) {}
			template <bool B>
			set_iterator(set_iterator<T, B> const &src) {
				_node = src.getNode();
			}
			~set_iterator() {}

			node_type		*getNode() const {
				return (_node);
			}

			set_iterator	&operator=(set_iterator const &rhs) {
				if (rhs._node != this->_node)
					this->_node = rhs._node;
				return (*this);
			}

			template <bool B>
			bool			operator==(set_iterator<T, B> const& rhs) const {
				return (this->_node == rhs.getNode());
			}

			template <bool B>
			bool			operator!=(set_iterator<T, B> const& rhs) const {
				return (!(*this == rhs));
			}

			reference		operator*() {
				return (this->_node->item);
			}

			reference		operator*() const {
				return (this->_node->item);
			}

			pointer		operator->() {
				return (&this->_node->item);
			}

			pointer		operator->() const {
				return (&this->_node->item);
			}

			set_iterator	&operator++() {
				_node = ft::next_node<value_type, false>(_node);
				return (*this);
			}

			set_iterator	operator++(int) {
				set_iterator	temp(*this);
				++(*this);
				return (temp);
			}

			set_iterator	&operator--() {
				_node = ft::prev_node<value_type, false>(_node);
				return (*this);
			}

			set_iterator	operator--(int) {
				set_iterator	temp(*this);
				--(*this);
				return (temp);
			}
	};

}

#endif
