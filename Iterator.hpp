/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:00:59 by fgata-va          #+#    #+#             */
/*   Updated: 2022/05/22 16:52:17 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <iterator>
# include <cstddef>
# include <iterator_traits.hpp>

namespace ft {
template <class T>
	class vector_iterator: public std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef typename iterator_traits<T*>::difference_type	difference_type;
			typedef typename iterator_traits<T*>::value_type		value_type;
			typedef typename iterator_traits<T*>::pointer			pointer;
			typedef typename iterator_traits<T*>::reference			reference;
			typedef typename iterator_traits<T*>::iterator_category	random_access_iterator_tag;

			vector_iterator(): _pointer(NULL) {}
			vector_iterator(T *src): _pointer(src) {}
			vector_iterator(vector_iterator const &src) { _pointer = src.getPointer(); }
			template <class U> vector_iterator(vector_iterator<U> const &src): _pointer(src.getPointer()) {}
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

			bool			operator==(vector_iterator const& rhs) const {
				return (this->_pointer == rhs.getPointer());
			}

			bool			operator!=(vector_iterator const& rhs) const {
				return (!(*this == rhs));
			}

			bool			operator<(vector_iterator const& rhs) const {
				return (this->_pointer < rhs.getPointer());
			}

			bool			operator>(vector_iterator const& rhs) const {
				return (rhs < *this);
			}

			bool			operator<=(vector_iterator const& rhs) const {
				return (this->_pointer <= rhs.getPointer());
			}

			bool			operator>=(vector_iterator const& rhs) const {
				return (rhs <= *this);
			}

			bool			operator<(vector_iterator const& rhs) const {
				return (this->_pointer < rhs.getPointer());
			}

			template <class U>
			bool			operator<(vector_iterator<U> const& rhs) const {
				return (this->_pointer < rhs.getPointer());
			}

			template <class U>
			bool			operator>(vector_iterator<U> const& rhs) const {
				return (rhs < *this);
			}

			template <class U>
			bool			operator<=(vector_iterator<U> const& rhs) const {
				return (this->_pointer <= rhs.getPointer());
			}

			template <class U>
			bool			operator>=(vector_iterator<U> const& rhs) const {
				return (rhs <= *this);
			}

			template <class U>
			bool			operator==(vector_iterator<U> const& rhs) const {
				return (this->_pointer == rhs.getPointer());
			}

			template <class U>
			bool			operator!=(vector_iterator<U> const& rhs) const {
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

			difference_type	operator+(vector_iterator const &lhs) const {
				return (this->_pointer + lhs._pointer);
			}

			difference_type	operator-(vector_iterator const &lhs) const {
				return (this->_pointer - lhs._pointer);
			}

			friend vector_iterator	operator+(int n, vector_iterator const& rhs) {
				return (rhs._pointer + n);
			}

			friend vector_iterator	operator-(int n, vector_iterator const& rhs) {
				return (rhs._pointer - n);
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
}

#endif
