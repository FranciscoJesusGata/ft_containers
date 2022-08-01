/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:48:51 by fgata-va          #+#    #+#             */
/*   Updated: 2022/08/01 22:22:35 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <iostream>

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
};

template <class T, class Compare, class Alloc>
struct RBTree
{
	typedef RBTreeNode<T>								node_type;
	node_type											*root;
	Compare												cmp;
	typename Alloc::template rebind<node_type>::other	node_allocator;

	RBTree(const Alloc &alloc = Alloc(), const Compare &comp = Compare()): root(NULL), cmp(comp), node_allocator(alloc) {}
	~RBTree() { delete_tree(root); }

	void	insert(const T &item) {
		node_type *parent = NULL;
		node_type *it = root;
		node_type *new_node;

		while (it)
		{
			parent = it;
			if (cmp(item, it->item)) {
				if (cmp(item, it->item))
					return ;
				it = it->left;
			}
			else
				it = it->right;
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

	node_type	*create_node(const T &item) {
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

};

template <class T>
void	in_order_print(RBTreeNode<T> *tree) {
	if (tree)
	{
		in_order_print(tree->left);
		std::cout << "[ "<< (tree->color ? "RED" : "BLACK") << " ]" << ": " << tree->item << std::endl;
		in_order_print(tree->right);
	}
}

template <class T >
void	pre_order_print(RBTreeNode<T> *tree) {
	if (tree)
	{
		std::cout << "[ "<< (tree->color ? "RED" : "BLACK") << " ]" << ": " << tree->item << std::endl;
		pre_order_print(tree->left);
		pre_order_print(tree->right);
	}
}

#endif