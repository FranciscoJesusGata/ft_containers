/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:13:17 by fgata-va          #+#    #+#             */
/*   Updated: 2022/09/15 22:08:19 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <utility.hpp>
# include <iterator_traits.hpp>
# include <RBTree.hpp>
# include <Iterator.hpp>
# include <algorithm.hpp>

namespace ft {
template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
	class map {
		public:
			typedef Key																			key_type;
			typedef T																			mapped_type;
			typedef ft::pair<const key_type, mapped_type>										value_type;
			typedef Compare																		key_compare;
			class value_compare {
				protected:
					Compare comp;
				public:
					value_compare (Compare c) : comp(c) {}
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef Alloc																						allocator_type;
			typedef typename allocator_type::reference															reference;
			typedef typename allocator_type::const_reference													const_reference;
			typedef typename allocator_type::pointer															pointer;
			typedef typename allocator_type::const_pointer														const_pointer;
			typedef typename ft::map_iterator<value_type, false>	iterator;
			typedef typename ft::map_iterator<value_type, true>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>														reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>												const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type										difference_type;
			typedef size_t																						size_type;

			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()): _tree(), _allocator(alloc), _size(0), _cmp(comp), _item_cmp(_cmp) {}

			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()): _tree(), _allocator(alloc), _size(0), _cmp(comp), _item_cmp(_cmp)
			{
				insert(first, last);
			}

			map (const map& x): _tree(), _allocator(x._allocator), _size(0), _cmp(x._cmp), _item_cmp(x._item_cmp) {
				*this = x;
			}

			~map () {}

			map					&operator= (const map& x)
			{
				if (*this != x) {
					clear();
					insert(x.begin(), x.end());
					_size = x.size();
				}
				return (*this);
			}

			iterator				begin() {
				return (iterator(_tree.min()));
			}

			const_iterator			begin() const {
				return (const_iterator(_tree.min()));
			}

			iterator				end() {
				return (++iterator(_tree.max()));
			}

			const_iterator			end() const {
				return (++const_iterator(_tree.max()));
			}

			reverse_iterator		rbegin() {
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(end()));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(begin()));
			}

			bool					empty() const {
				return (!_size);
			}

			size_type				size() const {
				return (_size);
			}

			size_type				max_size() const {
				return (_tree.max_size());
			}

			mapped_type				&operator[](const key_type& k) {
				return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
			}

			ft::pair<iterator,bool>	insert(const value_type& val)
			{
				ft::pair<node_type*,bool> inserted = _tree.insert(val);
				if (inserted.second)
					_size++;
				return (ft::make_pair<iterator, bool>(iterator(inserted.first), inserted.second));
			}

			iterator				insert(iterator position, const value_type& val)
			{
				ft::pair<node_type*, bool> inserted = _tree.insert(val, position.getNode());
				if (inserted.second)
					_size++;
				return (iterator(inserted.first));
			}

			template <class InputIterator>
			void					insert (InputIterator first, InputIterator last) {
				ft::pair<iterator,bool> inserted;
				for (; first != last ; first++) {
					inserted = insert(*first);
				}
			}
			/*
			void erase (iterator position);

			size_type erase (const key_type& k);

			void erase (iterator first, iterator last);
			*/ //I don't wanna face the delete valancing now I'm just postponing the inevitable here :')

			void					swap (map& x)
			{
				size_type aux_size = x._size;
				x._size = _size;
				_size = aux_size;
				_tree.swap(x._tree);
			}

			void					clear (void)
			{
				_tree.clear();
				_size = 0;
			}

			key_compare key_comp() const
			{
				return (key_compare());
			}

			value_compare value_comp() const
			{
				return (value_compare(_cmp));
			}

			iterator find (const key_type& k) {
				return (iterator(_tree.search(ft::make_pair(k,mapped_type()))));
			}

			const_iterator find (const key_type& k) const {
				return (const_iterator(_tree.search(ft::make_pair(k,mapped_type()))));
			}

			size_type count (const key_type& k) const
			{
				if (!this->_tree.search(ft::make_pair(k,mapped_type()))->nil)
					return (1);
				return (0);
			}

			iterator lower_bound (const key_type& k) {
				iterator it = begin(), finish = end();

				while (it != finish && _cmp(it->first, k))
					it++;
				return (it);
			}

			const_iterator lower_bound (const key_type& k) const {
				const_iterator it = begin(), finish = end();

				while (it != finish && _cmp(it->first, k))
					it++;
				return (it);
			}

			iterator upper_bound (const key_type& k) {
				iterator it = begin(), finish = end();

				while (it != finish && !_cmp(k, it->first))
					it++;
				return (it);
			}

			const_iterator upper_bound (const key_type& k) const {
				const_iterator it = begin(), finish = end();

				while (it != finish && !_cmp(k, it->first))
					it++;
				return (it);
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			pair<iterator,iterator>             equal_range (const key_type& k) {
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

		private:
			typedef ft::RBTree<value_type, value_compare, key_compare, allocator_type >	tree_type;
			typedef	ft::RBTreeNode<value_type>											node_type;
			tree_type																	_tree;
			Alloc																		_allocator;
			size_type																	_size;
			key_compare																	_cmp;
			value_compare																_item_cmp;
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
};

#endif
