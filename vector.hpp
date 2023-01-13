/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:38:33 by fgata-va          #+#    #+#             */
/*   Updated: 2023/01/08 19:29:07 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <type_traits.hpp>
# include <algorithm.hpp>
# include <functional>
# include <stdexcept>
# include <Iterator.hpp>
# include <typeinfo>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::vector_iterator<value_type, false>	iterator;
			typedef typename ft::vector_iterator<value_type, true>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef size_t											size_type;

			/**************
			* Contructors *
			***************/

			// Default constructor

			explicit vector(const allocator_type& alloc = allocator_type()):
				_allocator(alloc), _storadge(NULL), _size(0), _capacity(0)
			{}

			// Fill constructor

			explicit vector(size_type n, const value_type& val = value_type(), 
					const allocator_type& alloc = allocator_type()):
					_allocator(alloc), _storadge(_allocator.allocate(n)), _size(n), _capacity(n)
			{
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_storadge + i, val);
			}

			// Range constructor

			template <class InputIterator>
			vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
				InputIterator last, const allocator_type& alloc = allocator_type()):
				_allocator(alloc)
			{
				size_type		n = 0;
				pointer			pos;

				for (InputIterator it = first;it != last;it++)
					n++;
				this->_storadge = this->_allocator.allocate(n);
				this->_size = n;
				this->_capacity = n;
				pos = this->_storadge;
				while (first != last) {
					_allocator.construct(pos, *first);
					first++; pos++;
				}
			}

			// Copy constructor

			vector(const vector &x):
				_allocator(x._allocator), _size(x._size), _capacity(x._capacity)
			{
				this->_storadge = _allocator.allocate(_capacity);
				for (size_type n = 0; n < this->_size ; n++)
					_allocator.construct(_storadge + n, x[n]);
			}

			// Destrutor

			~vector(void) {
				for (size_type n = 0 ; n < this->_size ; n++)
					this->_allocator.destroy(this->_storadge + n);
				this->_allocator.deallocate(this->_storadge, this->_capacity);
			}

			// Equal operator

			vector&			operator=(const vector& x) {
				this->_allocator = x._allocator;
				for (size_type n = 0; n < this->_size; n++)
					_allocator.destroy(_storadge + n);
				if (this->_capacity < x._size) {
					_allocator.deallocate(_storadge, _capacity);
					this->_storadge = _allocator.allocate(x._size);
					this->_capacity = x._size;
				}
				this->_size = x._size;
				for (size_type n = 0; n < this->_size ; n++)
					_allocator.construct(_storadge + n, x[n]);
				return (*this);
			}

			/************
			* Iterators *
			*************/

			iterator begin()
			{
				return (iterator(this->_storadge));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_storadge));
			}

			iterator end()
			{
				return (iterator(this->_storadge + this->_size));
			}

			const_iterator end() const
			{
				return (const_iterator(this->_storadge + this->_size));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (reverse_iterator(end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return (reverse_iterator(begin()));
			}

			/**********************
			 * Capacity functions *
			 **********************/

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (this->_allocator.max_size());
			}

				/*
				 * Resize will change the number of elements to match
				 * the value especified by n.
				 *
				 * If n is lower than n, it will destroy the elements until
				 * the vector size is equal to n.
				 *
				 * If n is greater than size will call the default constructor
				 * of each element or use val if a default value is defined.
				 *
				 * If is also greater than the capacity it will make a reallocation
				 * of size n, and move the values to the new array
				 */

			void resize(size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw std::length_error("vector");
				if (n < this->_capacity) {
					if (n < this->_size) {
						for (size_type m = n; m < this->_size ; m++)
							this->_allocator.destroy(this->_storadge + m);
					}
					else if (n < this->_capacity && n > this->_size) {
						for (size_type m = this->_size ; m < n ; m++)
							this->_storadge[m] = val;
					}
				}
				else if (n > this->_capacity) {
					pointer new_storadge = this->_allocator.allocate(n);
					for (size_type m = 0; m < n; m++) {
						if (m < this->_size)
							this->_allocator.construct(new_storadge + m, this->_storadge[m]);
						else
							new_storadge[m] = val;
					}
					this->_allocator.deallocate(this->_storadge, this->_capacity);
					this->_storadge = new_storadge;
					this->_capacity = n;
				}
				this->_size = n;
			}

			size_type capacity() const
			{
				return (this->_capacity);
			}

			bool empty() const
			{
				if (!this->_size)
					return (true);
				return (false);
			}

			/*
			 * Reserve will request that the vector have, at least, the same capacity as n.
			 * So in case that n is greater than the current capacity will force a reallocation.
			 */

			void reserve(size_type n)
			{
				if (n > this->_capacity) {
					pointer new_storadge = this->_allocator.allocate(n);
					for (size_type m = 0; m < this->_size; m++) {
						this->_allocator.construct(new_storadge + m, this->_storadge[m]);
						_allocator.destroy(_storadge + m);
					}
					this->_allocator.deallocate(this->_storadge, this->_capacity);
					this->_storadge = new_storadge;
					this->_capacity = n;
				}
			}

			/******************
			 * Element access *
			 ******************/

			reference operator[](size_type n)
			{
				return (this->_storadge[n]);
			}

			const_reference operator[](size_type n) const
			{
				return (this->_storadge[n]);
			}

			reference at(size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return ((*this)[n]);
			}

			const_reference at(size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return ((*this)[n]);
			}

			reference front()
			{
				return (*(this->_storadge));
			}

			const_reference front() const
			{
				return (*(this->_storadge));
			}

			reference back()
			{
				return (*(this->_storadge + this->_size - 1));
			}

			const_reference back() const
			{
				return (*(this->_storadge + this->_size - 1));
			}

			/*************
			 * Modifiers *
			 *************/

			/*
			 * This function will assign new content to the vector,
			 * replacing the current content and modifying the size (and capacity) accordingly.
			 */

			// Range assing
			template <class InputIterator>
			void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
				InputIterator last)
			{
				size_t size = 0;
				size_t index = 0;
				InputIterator it = first;

				while (it != last) {
					size++; 
					it++;
				}
				if (size > this->_capacity)
					reserve(size);
				else if (size < _size)
				{
					for (size_t n = size ; n < _size ; n++)
						_allocator.destroy(_storadge + n);
				}
				it = first;
				while (index < size) {
					this->_storadge[index] = *it;
					index++; it++;
				}
				this->_size = size;
			}

			// Fill assing
			void	assign(size_type n, const value_type& val)
			{
				if (n > this->_capacity)
					reserve(n);
				else if (n < _size)
				{
					for (size_t i = n ; i < _size ; i++)
						_allocator.destroy(_storadge + i);
				}
				for (size_type m = 0; m < n; m++)
					this->_storadge[m] = val;
				this->_size = n;
			}

			/*
			 * This function will add elements at the end of the vector (_storadge[_size]),
			 * increasing size by 1 and reallocating if it's needed.
			 */

			void push_back(const value_type& val)
			{
				if (this->_size == this->_capacity) {
					if (this->_capacity <= 1)
						reserve(this->_capacity + 1);
					else
						reserve(this->_capacity + this->_capacity / 2);
				}
				_allocator.construct(_storadge + _size, val);
				_size++;
			}

			void pop_back()
			{
				_allocator.destroy(&back());
				_size--;
			}

			/*
			 * Insert:
			 * All of these functions will expand the vector in at the specified position increasing the size by
			 * the number of elements inserted. Will cause a reallocation if it's needed.
			 *
			 * The first function will insert one element of a specified value.
			 * The second function will insert as many elements as you specify with the same value.
			 * The third function will insert all the elements between two iterators. It will include the first
			 * but not the second iterator.
			 */

			iterator insert(iterator position, const value_type& val)
			{
				if (_size == _capacity) {
					vector<T>	new_vector;

					_reallocate(new_vector, 1);
					for (iterator it = begin(), ite = new_vector.begin(), last = new_vector.end(); ite != last; ite++) {
						if (it == position) {
							_allocator.construct(ite.getPointer(), val);
							position = ite;
						}
						else
							_allocator.construct(ite.getPointer(), *it++);
					}
					swap(new_vector);
				} else {
					_shift_right(position, 1);
					_allocator.construct(position.getPointer(), val);
					_size++;
				}
				return (position);
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				if (_size + n >= _capacity) {
					vector<T>	new_vector;

					_reallocate(new_vector, n);
					for (iterator it = begin(), ite = new_vector.begin(), last = end(); it <= last; ite++) {
						if (it == position)
							for (size_t i = 0; i < n; i++, ite++)
								_allocator.construct(ite.getPointer(), val);
						if (it == last)
							break ;
						_allocator.construct(ite.getPointer(), *it++);
					}
					swap(new_vector);
				} else {
					_shift_right(position, n);
					for (iterator it = position, last = position + n; it != last; it++)
						*it = val;
					_size += n;
				}	
			}

			template <class InputIterator>
			void insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				size_t	n = 0;

				for (InputIterator it = first; it != last ; it++, n++);
				if (_size + n >= _capacity) {
					vector<T>	new_vector;

					_reallocate(new_vector, n);
					for (iterator it = begin(), ite = new_vector.begin(), finish = end(); it <= finish; ite++) {
						for (;it == position && first != last; first++, ite++)
							_allocator.construct(ite.getPointer(), *first);
						if (it == finish)
							break ;
						_allocator.construct(ite.getPointer(), *it++);
					}
					swap(new_vector);
				} else {
					_shift_right(position, n);
					for (iterator it = position; first != last; it++, first++)
						*it = *first;
					_size += n;
				}
			}

			/*
			 * Erase:
			 * Will destroy the element in the indicated position or will destroy all the elements between two iterators,
			 * it will include the first but not the second iterator.
			 */

			iterator erase(iterator position)
			{
				for (iterator it = position, finish = end() - 1; it != finish; it++) {
					*it = *(it + 1);
				}
				_size--;
				_allocator.destroy(end().getPointer());
				return (position);
			}

			iterator erase(iterator first, iterator last)
			{
				size_t	n = last - first;

				for (iterator it = first, ite = last, finish = end(); ite != finish; it++, ite++) {
					*it = *ite;
				}
				_size -= n;
				for (iterator it = end(), finish = it + n; it < finish; it++)
					_allocator.destroy(it.getPointer());
				return (first);
			}

			void swap(vector& x)
			{
				pointer		tmp = x._storadge;
				size_type	tmp_size = x._size;
				size_type	tmp_capacity = x._capacity;

				x._storadge = _storadge;
				x._size = _size;
				x._capacity = _capacity;
				_storadge = tmp;
				_size = tmp_size;
				_capacity = tmp_capacity;
			}

			void clear()
			{
				for (size_type n = 0 ; n < this->_size ; n++)
					this->_allocator.destroy(this->_storadge + n);
				this->_size = 0;
			}

			allocator_type	get_allocator() const {
				return (this->allocator);
			}

		private:
			allocator_type	_allocator;
			pointer					_storadge;
			size_type				_size;
			size_type				_capacity;

			void _reallocate(vector<T> &src, size_type n)
			{
				size_type new_capacity =_capacity >> 1;

				if (n <= 0)
					return ;
				if (_size + n > new_capacity)
					src.reserve(_size + n);
				else
					src.reserve(new_capacity);
				src._size = _size + n;
			}

			void _shift_right(iterator position, size_type n)
			{
				for (iterator it = end() + n, ite = end(), last = position - 1 ; ite != last ; it--, ite--)
					_allocator.construct(it.getPointer(), *ite);
			}
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( lhs.size() == rhs.size() && ft::equal( lhs.begin(), lhs.end(), rhs.begin() ) );
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() ) );
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( !(rhs < lhs) );
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ( rhs < lhs );
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ( !(lhs < rhs) );
	}

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif
