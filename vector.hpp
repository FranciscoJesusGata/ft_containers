/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:38:33 by fgata-va          #+#    #+#             */
/*   Updated: 2022/05/12 21:31:26 by fgata-va         ###   ########.fr       */
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
			//Reverse iterator left
			typedef size_t										size_type;

			//Contructors
			vector (const allocator_type& alloc = allocator_type()): _allocator(alloc), _storadge(NULL), _size(0), _capacity(0) {}

			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
				_allocator(alloc), _storadge(_allocator.allocate(n)), _size(n), _capacity(n) {
				size_type	counter = 0;

				while (counter < n) {
					this->_storadge[counter] = val;
					counter++;
				}
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

			vector (const vector &x): _allocator(allocator_type()) {
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
				this->_storadge = _allocator.allocate(x._capacity);
				while (n < this->_size) {
					this->_storadge[n] = x._storadge[n];
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

			/*reverse_iterator		rbegin();
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
							new_storadge[m] = this->_storadge[m];
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
						new_storadge[m] = this->_storadge[m];
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
				this->_storadge[this->_size++] = val;
			}

			void			pop_back() {
				_allocator.destroy(&back());
				_size--;
			}

			iterator		insert (iterator position, const value_type& val) {
				value_type	aux;

				_size++;
				for (iterator it = position, last = end(); it != last; it++)
				{
					aux = *(it + 1);
					*(it + 1) = *it;
				}
				*position = val;
				return (position);
			}
			//void			insert (iterator position, size_type n, const value_type& val);
			/*template <class InputIterator>
			void			insert (iterator position, InputIterator first, InputIterator last);*/
			//iterator		erase (iterator position);
			//iterator		erase (iterator first, iterator last);

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
