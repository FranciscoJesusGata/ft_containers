/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:48:51 by fgata-va          #+#    #+#             */
/*   Updated: 2022/08/25 19:48:32 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <iostream>
# include <utility.hpp>

namespace ft {
	enum	e_color {BLACK, RED};
	enum	e_dir {LEFT, RIGHT};

	template <class T>
	struct RBTreeNode
	{
		struct RBTreeNode	*parent;
		struct RBTreeNode	*left;
		struct RBTreeNode	*right;
		e_color				color;
		T					item;

		RBTreeNode (): left(NULL), right(NULL), color(RED), item() {}
		RBTreeNode (const T &item): left(NULL), right(NULL), color(RED), item(item) {}
		~RBTreeNode () {}
	};

	template < class T, class Compare, class KeyComp, class Alloc>
	struct RBTree
	{
		typedef RBTreeNode<T>								node_type;
		typedef	T											value_type;
		node_type											*root;
		Compare												cmp;
		typename Alloc::template rebind<node_type>::other	node_allocator;

		RBTree(const Alloc &alloc = Alloc(), const Compare &comp = Compare(KeyComp())): root(NULL), cmp(comp), node_allocator(alloc) {}
		~RBTree() { delete_tree(root); }

		ft::pair<node_type*,bool>	insert(const value_type &item) {
			node_type	*parent = NULL;
			node_type	*it = root;
			node_type	*new_node;

			while (it)
			{
				parent = it;
				if (cmp(item, it->item))
					it = it->left;
				else if (cmp(it->item, item))
					it = it->right;
				else
					return (ft::make_pair<node_type*,bool>(it, false));
			}
			new_node = create_node(item);
			new_node->parent = parent;
			if (!parent)
				root = new_node;
			else if (cmp(new_node->item, parent->item))
				parent->left = new_node;
			else
				parent->right = new_node;
			insert_fixup(new_node);
			return (ft::make_pair<node_type*,bool>(new_node,true));
		}

		node_type	*search(const T &item) {
			node_type	*node = root;
			
			while (node)
			{
				if (cmp(node->item, item))
					node = node->left;
				else if (cmp(item, node->item))
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
			node_allocator.construct(node, node_type(item));
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

	template <class T>
	void	print_node(RBTreeNode<T> *tree) {	
		std::cout << "[ "<< (tree->color ? "RED" : "BLACK") << " ]";
		std::cout << ": [" << tree->item.first << " => " << tree->item.second << "]" << std::endl;
	}

	template <class T>
	void	in_order_mapi(RBTreeNode<T> *tree, void (*f)(RBTreeNode<T> *)) {
		if (tree)
		{
			in_order_mapi(tree->left, f);
			f(tree);
			in_order_mapi(tree->right, f);
		}
	}

	template <class T>
	void	pre_order_mapi(RBTreeNode<T> *tree, void (*f)(RBTreeNode<T> *)) {
		if (tree)
		{
			f(tree);
			pre_order_mapi(tree->left, f);
			pre_order_mapi(tree->right, f);
		}
	}
};

#endif