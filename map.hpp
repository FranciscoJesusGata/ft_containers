/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:13:17 by fgata-va          #+#    #+#             */
/*   Updated: 2022/09/01 19:09:06 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <utility.hpp>
# include <iterator_traits.hpp>
# include <RBTree.hpp>
# include <Iterator.hpp>

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
			typedef Alloc																					allocator_type;
			typedef typename allocator_type::reference														reference;
			typedef typename allocator_type::const_reference												const_reference;
			typedef typename allocator_type::pointer														pointer;
			typedef typename allocator_type::const_pointer													const_pointer;
			typedef typename ft::map_iterator<value_type, value_compare, key_compare, allocator_type>		iterator;
			typedef typename ft::map_iterator<const value_type, value_compare, key_compare, allocator_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>													reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>											const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type									difference_type;
			typedef size_t																					size_type;

			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()): _tree(), _allocator(alloc), _size(0), _cmp(comp), _item_cmp(_cmp) {}

			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()): _tree(), _allocator(alloc), _size(0), _cmp(comp), _item_cmp(_cmp)
			{
				insert(first, last);
			}

			map (const map& x): _tree(x._tree), _allocator(x._allocator), _size(0), _cmp(x._cmp), _item_cmp(x._item_cmp) {
				if (*this != x)
					*this = x;
				return (*this);
			}

			~map () {}

			/*
			map					&operator= (const map& x)
			{
				
			}
			*/
			iterator				begin() {
				node_type	*node = _tree.root;
				while (node->left)
					node = node->left;
				return (iterator(node, &_tree));
			}

			iterator				end() {
				return (iterator(NULL, &_tree));
			}

			const_iterator			cbegin() const {
				node_type	*node = _tree.root;
				while (node->left)
					node = node->left;
				return (const_iterator(node, &_tree));
			}

			const_iterator 			cend() const {
				return (const_iterator(NULL, &_tree));
			}

			reverse_iterator		rbegin() {
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	crbegin() const {
				return (const_reverse_iterator(cend()));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	crend() {
				return (const_reverse_iterator(cbegin()));
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
			
			mapped_type				&at(const key_type& k) {
				node_type	*found = _tree.search(ft::make_pair(k,mapped_type()));

				if (!found)
					throw std::out_of_range("map::at:  key not found");
				return (found->item.second);
			}

			const mapped_type&		at(const key_type& k) const {
				node_type	*found = _tree.search(k);

				if (!found)
					throw std::out_of_range("map::at:  key not found");
				return (found->item.second);
			}

			ft::pair<iterator,bool>	insert(const value_type& val)
			{
				ft::pair<node_type*,bool> item = _tree.insert(val);
				if (item.second)
					_size++;
				return (ft::make_pair<iterator, bool>(iterator(item.first, &_tree), item.second));
			}

			iterator				insert(iterator position, const value_type& val)
			{
				node_type	*hint = position.getNode();
				ft::pair<node_type*, bool> inserted;

				if (!hint || position.getTree() != &_tree)
					return (insert(val).first);
				for (node_type *p = hint->parent ; p ; p = p->parent) {
					if (_item_cmp(p->item, p->parent->item) != _item_cmp(val, p->parent->item))
						return (insert(val).first);
				}
				inserted = _tree.insert(val, hint);
				if (inserted.second)
					_size++;
				return (iterator(inserted.first, &_tree));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) {
				ft::pair<iterator,bool> inserted;
				for (; first != last ; first++) {
					inserted = insert(*first);
				}
			}
			/*
			void erase (iterator position);

			size_type erase (const key_type& k);

			void erase (iterator first, iterator last);
			*/

		private:
			typedef ft::RBTree<value_type, value_compare, key_compare, allocator_type >	tree_type;
			typedef	ft::RBTreeNode<value_type>											node_type;
			tree_type																	_tree;
			Alloc																		_allocator;
			size_type																	_size;
			key_compare																	_cmp;
			value_compare																_item_cmp;
			friend struct																ft::RBTree<value_type, value_compare, key_compare, allocator_type>;
	};
};

#endif