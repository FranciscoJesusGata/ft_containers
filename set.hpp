/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:09:22 by fgata-va          #+#    #+#             */
/*   Updated: 2022/09/29 22:10:00 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include <memory>
# include <utility.hpp>
# include <iterator_traits.hpp>
# include <RBTree.hpp>
# include <Iterator.hpp>
# include <algorithm.hpp>

namespace ft {
template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
  class set {
    public:
      typedef T	  																									  key_type;
			typedef T	                                    								  value_type;
			typedef Compare																								  key_compare;
			typedef Compare                                                 value_compare;	
			typedef Alloc																										allocator_type;
			typedef typename allocator_type::reference											reference;
			typedef typename allocator_type::const_reference								const_reference;
			typedef typename allocator_type::pointer												pointer;
			typedef typename allocator_type::const_pointer									const_pointer;
			typedef typename ft::set_iterator<value_type, false>						iterator;
			typedef typename ft::set_iterator<value_type, true>							const_iterator;
			typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t																									size_type;

			explicit set (const key_compare& comp = key_compare(),
			  const allocator_type& alloc = allocator_type()):  _tree(), _allocator(alloc), _size(0), _cmp(comp) {}

      template <class InputIterator>
      set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
          const allocator_type& alloc = allocator_type()):  _tree(), _allocator(alloc), _size(0), _cmp(comp) {
        insert(first, last);
      }

      set (const set& x):  _tree(), _allocator(x._allocator), _size(0), _cmp(x._cmp) {
        *this = x;
      }

      ~set () {}

      set& operator= (const set& x) {
        clear();
        insert(x.begin(), x.end());
        _size = x.size();
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

      ft::pair<iterator,bool> insert (const value_type& val) {
        ft::pair<node_type*,bool> inserted = _tree.insert(val);
				if (inserted.second)
					_size++;
				return (ft::make_pair<iterator, bool>(iterator(inserted.first), inserted.second));
      }

			iterator				insert(iterator position, const value_type& val) {
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

      void erase (iterator position) {
				_tree.erase(position.getNode());	
				_size--;
			}

			size_type erase (const value_type& val) {
				if (_tree.erase(val)) {
					_size--;
					return (1);
				}
				return (0);
			}

			void erase (iterator first, iterator last) {
				iterator	tmp;
				while (first != last) {
					tmp = first;
					first++;
					erase(tmp);
				}
			}

      void					swap (set& x) {
				size_type aux_size = x._size;
				x._size = _size;
				_size = aux_size;
				_tree.swap(x._tree);
			}

      void					clear (void) {
				_tree.clear();
				_size = 0;
			}

      key_compare key_comp() const {
				return (key_compare());
			}

			value_compare value_comp() const {
				return (value_compare());
			}

      iterator find (const value_type& val) {
				return (iterator(_tree.search(val)));
			}

			const_iterator find (const value_type& val) const {
				return (const_iterator(_tree.search(val)));
			}

			size_type count (const value_type& val) const
			{
				if (!this->_tree.search(val)->nil)
					return (1);
				return (0);
			}

			iterator lower_bound (const value_type& val) {
				iterator it = begin(), finish = end();

				while (it != finish && _cmp(*it, val))
					it++;
				return (it);
			}

			const_iterator lower_bound (const value_type& val) const {
				const_iterator it = begin(), finish = end();

				while (it != finish && _cmp(*it, val))
					it++;
				return (it);
			}

			iterator upper_bound (const value_type& val) {
				iterator it = begin(), finish = end();

				while (it != finish && !_cmp(val, *it))
					it++;
				return (it);
			}

			const_iterator upper_bound (const value_type& val) const {
				const_iterator it = begin(), finish = end();

				while (it != finish && !_cmp(val, *it))
					it++;
				return (it);
			}

			pair<const_iterator,const_iterator> equal_range (const value_type& val) const {
				return (ft::make_pair(lower_bound(val), upper_bound(val)));
			}

			pair<iterator,iterator>             equal_range (const value_type& val) {
				return (ft::make_pair(lower_bound(val), upper_bound(val)));
			}

      allocator_type get_allocator() const {
        return (allocator_type());
      }

    private:
      typedef ft::RBTree<const value_type, value_compare, key_compare, allocator_type>	tree_type;
			typedef	ft::RBTreeNode<const value_type>  																				node_type;
			tree_type														   																			_tree;
			Alloc																	   																		_allocator;
			size_type																  																	_size;
			value_compare   													  																_cmp;
 };

  template <class T, class Compare, class Alloc>
	bool operator== ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Compare, class Alloc>
	bool operator!= ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator<  ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<= ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>  ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>= ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
	
	template <class T, class Compare, class Alloc>
	void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
};

#endif
