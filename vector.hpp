/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:38:33 by fgata-va          #+#    #+#             */
/*   Updated: 2022/04/27 17:30:02 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <type_traits.hpp>

# include <iostream>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference ;
			typedef typename allocator_type::const_reference	const_reference ;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer ;
			//Iterator, const iterator and reverse iterator left
			typedef size_t										size_type;

			//Contructors
			vector (const allocator_type& alloc = allocator_type()): _allocator(alloc), _storage(NULL), _size(0), _capacity(0) {}

			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
				_allocator(alloc), _storage(_allocator.allocate(n)), _size(n), _capacity(n) {
				size_type	counter = 0;

				while (counter < n) {
					this->_storage[counter] = val;
					counter++;
				}
			}

			template <class InputIterator, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type()): _allocator(alloc) {
				size_type		n;
				pointer			pos;

				for (InputIterator it = first;it != last;it++)
					n++;
				this->_storage = this->_allocator.allocate(n);
				this->_size = n;
				this->_capacity = n;
				pos = this->_storage;
				while (first != last) {
					*pos = *first;
					first++; pos++;
				}
			}

			vector (const vector &x): _allocator(allocator_type()) {
				if (*this != x)
					*this = x;
			}

			~vector(void) {
				size_type counter = 0;

				while (counter < this->_size) {
					this->_allocator.destroy(this->_storage + counter);
					counter++;
				}
				this->_allocator.deallocate(this->_storage, this->_capacity);
			}

			vector&			operator= (const vector& x) {
				size_type		n = 0;

				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_storage = _allocator.allocate(x._capacity);
				while (n < this->_size) {
					this->_storage[n] = x._storage[n];
					n++;
				}
				return (*this);
			}

			/*
			iterator		begin();
			const_iterator	begin() const;
			iterator		end();
			const_iterator	end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;
			*/

			//Capacity functions
			size_type		size() const {
				return (this->_size);
			}

			size_type		max_size() const {
				return (this->_allocator.max_size());
			}

			/*void			resize(size_type n, value_type val = value_type()) {
				
			}*/
			size_type		capacity() const;
			bool			empty() const;
			void			reverse(size_type n);

			reference		operator[] (size_type n);
			const_reference	operator[] (size_type n) const;
			reference		at (size_type n);
			const_reference	at (size_type n) const;
			reference		front();
			const_reference	front() const;
			reference		back();
			const_reference	back() const;

			template <class InputIterator>
			void			assign (InputIterator first, InputIterator last);
			void			assign (size_type n, const value_type& val);
			void			push_back (const value_type& val);
			void			pop_back();
			//iterator		insert (iterator position, const value_type& val);
			//void			insert (iterator position, size_type n, const value_type& val);
			/*template <class InputIterator>
			void			insert (iterator position, InputIterator first, InputIterator last);*/
			//iterator		erase (iterator position);
			//iterator		erase (iterator first, iterator last);
			void			swap (vector& x);
			void			clear();

			allocator_type	get_allocator() const;
		private:
			allocator_type	_allocator;
			pointer			_storage;
			size_type		_size;
			size_type		_capacity;
	};

template <class T, class Alloc>
bool	operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool	operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool	operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool	operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool	operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
void	swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

}

#endif
