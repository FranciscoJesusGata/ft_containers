/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:13:17 by fgata-va          #+#    #+#             */
/*   Updated: 2022/08/03 00:28:36 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <utility.hpp>
# include <iterator_traits.hpp>
# include <RBTree.hpp>

namespace ft {
template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
	class map {
		private:
			typedef ft::RBTree<ft::pair<const Key, T>, Compare, Alloc >							tree_type;
			typedef	ft::RBTreeNode<ft::pair<const Key, T> >										node_type;
		public:
			typedef Key																			key_type;
			typedef T																			mapped_type;
			typedef ft::pair<const key_type, mapped_type>										value_type;
			typedef Compare																		key_compare;
			class																				value_compare;
			typedef Alloc																		allocator_type;
			typedef typename allocator_type::reference											reference;
			typedef typename allocator_type::const_reference									const_reference;
			typedef typename allocator_type::pointer											pointer;
			typedef typename allocator_type::const_pointer										const_pointer;
			typedef typename ft::map_iterator<value_type, key_compare, allocator_type>			iterator;
			typedef typename ft::map_iterator<const value_type, key_compare, allocator_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>										reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>								const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type						difference_type;
			typedef size_t																		size_type;

			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()): _tree(), _allocator(alloc), _size(0), _cmp(comp) {}

			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()): _tree(), _allocator(alloc), _size(0), _cmp(comp)
			{
				for (;first != last;first++) {
					_tree.insert(*first);
					_size++;
				}
			}

			/*map (const map& x) {
				if (*this != x)
					*this = x;
				return (*this);
			}*/

			~map () {}

			iterator begin() {
				node_type	*node = _tree->root;
				while (node->left)
					node = node->left;
				return (iterator(node, &_tree));
			}

			const_iterator begin() const {
				node_type	*node = _tree->root;
				while (node->left)
					node = node->left;
				return (const_iterator(node, &_tree));
			}

			iterator end() {
				return (iterator(NULL));
			}
			const_iterator end() const {
				return (const_iterator(NULL));
			}

			bool empty() const {
				return (!_size);
			}

			size_type size() const {
				return (_size);
			}

			size_type max_size() const {
				return (_tree.max_size());
			}


		private:
			tree_type	_tree;
			Alloc		_allocator;
			size_type	_size;
			key_compare	_cmp;
	};

	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare
	{
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
	};
};

#endif