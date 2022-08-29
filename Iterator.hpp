/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:00:59 by fgata-va          #+#    #+#             */
/*   Updated: 2022/08/29 12:29:19 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
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

	template <class T>
	class vector_iterator: public std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T*>::value_type		value_type;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef typename ft::iterator_traits<T*>::iterator_category	random_access_iterator_tag;

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

	template <class T, class Cmp, class KeyCmp, class Alloc>
	class map_iterator: public std::iterator<std::bidirectional_iterator_tag, T, Cmp> {
		private:
			typedef ft::RBTreeNode<T>									node_type;
			typedef ft::RBTree<T, Cmp, KeyCmp, Alloc>					tree_type;
			node_type													*_node;
			tree_type													*_tree;
		public:
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T*>::value_type		value_type;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef typename ft::iterator_traits<T*>::iterator_category	random_access_iterator_tag;

			map_iterator(tree_type *src_tree): _node(NULL), _tree(src_tree) {}
			map_iterator(node_type *src, tree_type *src_tree): _node(src), _tree(src_tree) {}
			map_iterator(map_iterator const &src): _node(src.getNode()), _tree(src.getTree()) {}
			template <class U> map_iterator(map_iterator<U, Cmp, KeyCmp, Alloc> const &src): _node(src.getNode()), _tree(src.getTree()) {}
			~map_iterator() {}

			node_type		*getNode() const {
				return (_node);
			}

			tree_type		*getTree() const {
				return (_tree);
			}
			map_iterator	&operator=(map_iterator const &rhs) {
				if (rhs._node != this->_node)
					this->_node = rhs._node;
				return (*this);
			}

			template <class U>
			bool			operator==(map_iterator<U, Cmp, KeyCmp, Alloc> const& rhs) const {
				return (this->_node == rhs.getNode());
			}

			template <class U>
			bool			operator!=(map_iterator<U, Cmp, KeyCmp, Alloc> const& rhs) const {
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
				if (_node) {
					if (_node->right) {
						_node = _node->right;
						while (_node->left)
							_node = _node->left;
					}
					else {
						while (_node->parent && _node == _node->parent->right)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				else {
					_node = _tree->root;
					while (_node)
						_node = _node->left;
				}
				return (*this);
			}

			map_iterator	operator++(int) {
				map_iterator	temp(*this);
				++(*this);
				return (temp);
			}

			map_iterator	&operator--() {
				if (_node) {
					if (_node->left) {
						_node = _node->left;
						while (_node->right)
							_node = _node->right;
					}
					else {
						while (_node->parent && _node == _node->parent->left)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				else {
					_node = _tree->root;
					while (_node)
						_node = _node->right;
				}
				return (*this);
			}

			map_iterator	operator--(int) {
				map_iterator	temp(*this);
				--this->_pointer;
				return (temp);
			}
	};
}

#endif
