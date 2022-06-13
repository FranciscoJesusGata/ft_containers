/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:38:33 by fgata-va          #+#    #+#             */
/*   Updated: 2022/06/13 12:45:58 by fgata-va         ###   ########.fr       */
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
# include <iostream>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference ;
			typedef typename allocator_type::const_reference		const_reference ;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer ;
			typedef typename ft::vector_iterator<value_type>		iterator;
			typedef typename ft::vector_iterator<value_type const>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef size_t											size_type;

			//Contructors
			vector (const allocator_type& alloc = allocator_type()): _allocator(alloc), _storadge(NULL), _size(0), _capacity(0) {}

			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
				_allocator(alloc), _storadge(_allocator.allocate(n)), _size(n), _capacity(n) {
				
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_storadge + i, val);
			}

			template <class InputIterator>
			vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
				const allocator_type& alloc = allocator_type()):_allocator(alloc) {
				size_type		n = 0;
				pointer			pos;

				for (InputIterator it = first;it != last;it++)
					n++;
				this->_storadge = this->_allocator.allocate(n);
				this->_size = n;
				this->_capacity = n;
				pos = this->_storadge;
				while (first != last) {
					*pos = *first;
					first++; pos++;
				}
			}

			vector (const vector &x) {
				if (*this != x)
					*this = x;
			}

			~vector(void) {
				size_type counter = 0;

				while (counter < this->_size) {
					this->_allocator.destroy(this->_storadge + counter);
					counter++;
				}
				this->_allocator.deallocate(this->_storadge, this->_capacity);
			}

			vector&			operator= (const vector& x) {
				size_type		n = 0;

				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_allocator = x._allocator;
				this->_storadge = _allocator.allocate(x._capacity);
				while (n < this->_size) {
					_allocator.construct(_storadge + n, x[n]);
					n++;
				}
				return (*this);
			}

			iterator		begin() {
				return (iterator(this->_storadge));
			}

			const_iterator	begin() const {
				return (const_iterator(this->_storadge));
			}

			iterator		end() {
				return (iterator(this->_storadge + this->_size));
			}

			const_iterator	end() const {
				return (const_iterator(this->_storadge + this->_size));
			}

			reverse_iterator		rbegin() {
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const {
				return (reverse_iterator(end()));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const {
				return (reverse_iterator(begin()));
			}


			//Capacity functions
			size_type		size() const {
				return (this->_size);
			}

			size_type		max_size() const {
				return (this->_allocator.max_size());
			}

			void			resize(size_type n, value_type val = value_type()) {
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

			size_type		capacity() const {
				return (this->_capacity);
			}

			bool			empty() const {
				if (!this->_size)
					return (true);
				return (false);
			}

			void			reserve(size_type n) {
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

			reference		operator[] (size_type n) {
				return (this->_storadge[n]);
			}

			const_reference	operator[] (size_type n) const {
				return (this->_storadge[n]);
			}

			reference		at (size_type n) {
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return ((*this)[n]);
			}

			const_reference	at (size_type n) const {
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return ((*this)[n]);
			}

			reference		front() {
				return (*(this->_storadge));
			}

			const_reference	front() const {
				return (*(this->_storadge));
			}

			reference		back() {
				return (*(this->_storadge + this->_size - 1));
			}

			const_reference	back() const {
				return (*(this->_storadge + this->_size - 1));
			}

			template <class InputIterator>
			void			assign
				(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
				size_t size = 0;
				size_t index = 0;
				InputIterator it = first;

				while (it != last) {
					size++; 
					it++;
				}
				if (size > this->_capacity) {
					pointer new_storadge = this->_allocator.allocate(size);
					this->_allocator.deallocate(this->_storadge, this->_capacity);
					this->_storadge = new_storadge;
					this->_capacity = size;
				}
				it = first;
				while (index < size) {
					this->_storadge[index] = *it;
					index++; it++;
				}
				this->_size = size;
			}

			void			assign (size_type n, const value_type& val) {
				if (n > this->_capacity) {
					pointer new_storadge = this->_allocator.allocate(n);
					this->_allocator.deallocate(this->_storadge, this->_capacity);
					this->_storadge = new_storadge;
					this->_capacity = n;
				}
				for (size_type m = 0; m < n; m++)
					this->_storadge[m] = val;
				this->_size = n;
			}

			void			push_back (const value_type& val) {
				if (this->_size == this->_capacity) {
					if (this->_capacity <= 1)
						reserve(this->_capacity + 1);
					else
						reserve(this->_capacity + this->_capacity / 2);
				}
				_allocator.construct(_storadge + _size, val);
				_size++;
			}

			void			pop_back() {
				_allocator.destroy(&back());
				_size--;
			}

			iterator		insert (iterator position, const value_type& val) {
				if (_size == _capacity || position >= end()) {
					vector<T>	new_vector;
					if (position > end())
						_reallocate(new_vector, position - end() + 1);
					else
						_reallocate(new_vector, 1);
					for (iterator it = begin(), ite = new_vector.begin(), last = new_vector.end(); ite != last; ite++) {
						if (it == position) {
							*ite = val;
							position = ite;
						}
						else
							*ite = *it++;
					}
					swap(new_vector);
				} else {
					_shift_right(position, 1);
					*position = val;
					_size++;
				}
				return (position);
			}

			void			insert (iterator position, size_type n, const value_type& val) {
				if (_size + n >= _capacity) {
					vector<T>	new_vector;
					_reallocate(new_vector, n);
					for (iterator it = begin(), ite = new_vector.begin(), last = end(); it <= last; ite++) {
						if (it == position)
							for (size_t i = 0; i < n; i++, ite++)
								*ite = val;
						if (it == last)
							break ;
						*ite = *it++;
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
			void			insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
				size_t	n = 0;

				for (InputIterator it = first; it != last ; it++, n++);
				if (_size + n >= _capacity) {
					vector<T>	new_vector;
					_reallocate(new_vector, n);
					for (iterator it = begin(), ite = new_vector.begin(), finish = end(); it <= finish; ite++) {
						for (;it == position && first != last; first++, ite++)
							*ite = *first;
						if (it == finish)
							break ;
						*ite = *it++;
					}
					swap(new_vector);
				} else {
					_shift_right(position, n);
					for (iterator it = position; first != last; it++, first++)
						*it = *first;
					_size += n;
				}
			}

			iterator		erase (iterator position) {
				for (iterator it = position, finish = end() - 1; it != finish; it++) {
					*it = *(it + 1);
				}
				_allocator.destroy(end().getPointer());
				_size--;
				return (position);
			}

			iterator		erase (iterator first, iterator last) {
				size_t	n = last - first;

				for (iterator it = first, ite = last, finish = end(); it != finish; it++, ite++) {
					*it = *ite;
				}
				for (iterator it = end(), finish = it + n; it < finish; it++)
					_allocator.destroy(it.getPointer());
				_size -= n;
				return (first);
			}

			void			swap (vector& x) {
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

			void			clear() {
				for (size_type n = 0 ; n < this->_size ; n++)
					this->_allocator.destroy(this->_storadge + n);
				this->_size = 0;
			}

			allocator_type	get_allocator() const {
				return (this->allocator);
			}

		private:
			allocator_type	_allocator;
			pointer			_storadge;
			size_type		_size;
			size_type		_capacity;

			void	_reallocate(vector<T> &src, size_type n) {
				if (_capacity + n <= 1)
					src.reserve(_capacity + 1);
				else if (_size + n <= (_capacity + _capacity / 2))
					src.reserve(_capacity + _capacity / 2);
				else
					src.reserve((_capacity + _capacity / 2) + n);
				src._size = _size + n;
			}

			void	_shift_right(iterator position, size_type n) {
				for (iterator it = end() + n, ite = end(), last = position ; ite != last ; it--, ite--)
					*it = *ite;
			}
	};

	template <class T, class Alloc>
	bool	operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ( lhs.size() == rhs.size() && ft::equal( lhs.begin(), lhs.end(), rhs.begin() ) );
	}

	template <class T, class Alloc>
	bool	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ( ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() ) );
	}

	template <class T, class Alloc>
	bool	operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ( !(rhs < lhs) );
	}

	template <class T, class Alloc>
	bool	operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ( rhs < lhs );
	}

	template <class T, class Alloc>
	bool	operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ( !(lhs < rhs) );
	}

	template <class T, class Alloc>
	void	swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

}

#endif
