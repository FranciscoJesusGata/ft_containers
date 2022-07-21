/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:48:51 by fgata-va          #+#    #+#             */
/*   Updated: 2022/07/21 20:48:47 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <iostream>

enum	e_color {BLACK, RED};
enum	e_dir {LEFT, RIGHT};

template <class T, class Alloc >
struct RBTreeNode
{
	struct RBTreeNode	*parent;
	struct RBTreeNode	*left;
	struct RBTreeNode	*right;
	e_color				color;
	Alloc				allocator;
	T					item;

	RBTreeNode(const T &val, Alloc allocator = Alloc()): parent(NULL), left(NULL), right(NULL), color(RED), allocator(allocator) { allocator.construct(&item, val); }
	~RBTreeNode() { allocator.destroy(&item); }
};

template <class T, class Compare, class Alloc>
struct RBTree
{
	typedef RBTreeNode<T, Alloc>	Node;
	Node							*root;
	Compare							cmp;
	Alloc							allocator;

	RBTree(const Alloc &alloc = Alloc(), const Compare &comp = Compare()): root(NULL), cmp(comp), allocator(alloc) {}
	~RBTree() { delete_tree(root); }

	void	insert(const T &item) {
		Node *parent = NULL;
		Node *it = root;
		Node *new_node = new Node(item);

		while (it)
		{
			parent = it;
			if (cmp(new_node->item, it->item))
				it = it->left;
			else
				it = it->right;
		}
		new_node->parent = parent;
		if (!parent)
			root = new_node;
		else if (cmp(new_node->item, parent->item))
			parent->left = new_node;
		else
			parent->right = new_node;
		insert_fixup(new_node);
	}

	Node	*rotate(Node *node, int dir) {
		Node	*son = (dir ? node->left : node->right);
		Node	*grandson;
		Node	*grandpa;

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

	void	insert_fixup(Node *new_node)
	{
		Node *parent = new_node->parent;
		Node *uncle;
		Node *grandpa;

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

	void	delete_tree(Node *tree) {
		if (tree)
		{
			delete_tree(tree->left);
			delete_tree(tree->right);
			delete tree;
			tree = NULL;
		}
	}

};

template <class T, class Alloc >
void	in_order_print(RBTreeNode<T, Alloc> *tree) {
	if (tree)
	{
		in_order_print(tree->left);
		std::cout << "[ "<< (tree->color ? "RED" : "BLACK") << " ]" << ": " << tree->item << std::endl;
		in_order_print(tree->right);
	}
}

template <class T, class Alloc >
void	pre_order_print(RBTreeNode<T, Alloc> *tree) {
	if (tree)
	{
		std::cout << "[ "<< (tree->color ? "RED" : "BLACK") << " ]" << ": " << tree->item << std::endl;
		pre_order_print(tree->left);
		pre_order_print(tree->right);
	}
}

#endif