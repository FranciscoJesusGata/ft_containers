/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:48:51 by fgata-va          #+#    #+#             */
/*   Updated: 2022/08/18 13:17:49 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <iostream>
# include <utility.hpp>

namespace ft {
	enum	e_color {BLACK, RED};
	enum	e_dir {LEFT, RIGHT};

	template <class Key, class T>
	struct RBTreeNode
	{
		struct RBTreeNode	*parent;
		struct RBTreeNode	*left;
		struct RBTreeNode	*right;
		e_color				color;
		ft::pair<Key, T>	item;
	};

	template <class Key, class T, class Compare, class Alloc>
	struct RBTree
	{
		typedef RBTreeNode<Key, T>							node_type;
		typedef	ft::pair<Key,T>								value_type;
		node_type											*root;
		Compare												cmp;
		typename Alloc::template rebind<node_type>::other	node_allocator;

		RBTree(const Alloc &alloc = Alloc(), const Compare &comp = Compare()): root(NULL), cmp(comp), node_allocator(alloc) {}
		~RBTree() { delete_tree(root); }

		node_type	*insert(const value_type &item) {
			node_type	*parent = NULL;
			node_type	*it = root;
			node_type	*new_node;

			while (it)
			{
				parent = it;
				if (cmp(item.first, it->item.first))
					it = it->left;
				else if (cmp(it->item.first, item.first))
					it = it->right;
				else
					return (NULL);
			}
			new_node = create_node(item);
			new_node->parent = parent;
			if (!parent)
				root = new_node;
			else if (cmp(new_node->item.first, parent->item.first))
				parent->left = new_node;
			else
				parent->right = new_node;
			insert_fixup(new_node);
			return (new_node);
		}

		node_type	*search(node_type *node, Key &key) {
			while (node)
			{
				if (cmp(node->item.first, key))
					node = node->left;
				else if (cmp(key, node->item.first))
					node = node->right;
				else
					break ;
			}
			return (node);
		}

		node_type	*rotate(node_type *node, int dir) {
			node_type	*son = (dir ? node->left : node->right);
			node_type	*grandson;
			node_type	*grandpa;

			if (!son)
				return (NULL);
			grandson = (dir ? son->right : son->left);
			if (grandson)
				grandson->parent = node;
			(dir ? node->left : node->right) = grandson;
			(dir ? son->right : son->left) = node;
			grandpa = node->parent;
			son->parent = grandpa;
			node->parent = son;
			if (grandpa)
				(node == grandpa->right ? grandpa->right : grandpa->left) = son;
			else
				root = son;
			return (son);
		}

		private:

		void	insert_fixup(node_type *new_node)
		{
			node_type *parent = new_node->parent;
			node_type *uncle;
			node_type *grandpa;

			while (parent && parent->color == RED)
			{
				uncle = (parent == parent->parent->left ? parent->parent->right : parent->parent->left);
				if (uncle && uncle->color == RED) {
					parent->color = BLACK;
					parent->parent->color = RED;
					uncle->color = BLACK;
					new_node = parent->parent;
				}
				else if ((new_node == parent->left && parent == parent->parent->right)
					|| (new_node == parent->right && parent == parent->parent->left)) {
						if (new_node == parent->left)
							rotate(parent, RIGHT);
						else
							rotate(parent, LEFT);
						new_node = parent;
				}
				else {
					grandpa = parent->parent;
					if (new_node == parent->left)
						rotate(grandpa, RIGHT);
					else
						rotate(grandpa, LEFT);
					parent->color = BLACK;
					grandpa->color = RED;
				}
				parent = new_node->parent;
			}
			root->color = BLACK;
		}
		
		node_type	*create_node(const value_type &item) {
			node_type *node;
		
			node = node_allocator.allocate(sizeof(node_type));
			node->item = item;
			node->color = RED;
			node->left = NULL;
			node->right = NULL;
			return (node);
		}

		void		destroy_node(node_type *node) {
			node_allocator.destroy(&node);
			node_allocator.deallocate(&node, sizeof(node_type));
		}


		void	delete_tree(node_type *tree) {
			if (tree)
			{
				delete_tree(tree->left);
				delete_tree(tree->right);
				node_allocator.destroy(tree);
				node_allocator.deallocate(tree, sizeof(node_type));
				tree = NULL;
			}
		}

		void	max_size() {
			return (node_allocator.max_size());
		}
	};

	template <class Key, class T>
	void	print_node(RBTreeNode<Key, T> *tree) {	
		std::cout << "[ "<< (tree->color ? "RED" : "BLACK") << " ]";
		std::cout << ": [" << tree->item.first << " => " << tree->item.second << "]" << std::endl;
	}

	template <class Key, class T>
	void	in_order_mapi(RBTreeNode<Key, T> *tree, void (*f)(RBTreeNode<Key, T> *)) {
		if (tree)
		{
			in_order_mapi(tree->left, f);
			f(tree);
			in_order_mapi(tree->right, f);
		}
	}

	template <class Key, class T>
	void	pre_order_mapi(RBTreeNode<Key, T> *tree, void (*f)(RBTreeNode<Key, T> *)) {
		if (tree)
		{
			f(tree);
			pre_order_mapi(tree->left, f);
			pre_order_mapi(tree->right, f);
		}
	}
};

#endif