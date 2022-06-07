/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:48:51 by fgata-va          #+#    #+#             */
/*   Updated: 2022/06/07 21:14:00 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <iostream>

enum	e_color {BLACK, RED};

template <class T, class Alloc >
struct RBTreeNode
{
	struct RBTreeNode	*parent;
	struct RBTreeNode	*left;
	struct RBTreeNode	*right;
	e_color				color;
	Alloc				allocator;
	T					item;

	RBTreeNode(const T &val, Alloc allocator = Alloc()): parent(NULL), left(NULL), right(NULL), color(RED), allocator(allocator), item(val) {}
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
	~RBTree() {
		delete_tree(root);
	}

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
	}
	
	Node	*rotate(Node *node, int dir) {
		Node	*son = (dir ? node->left : node->right);
		Node	*grand_son;
		Node	*grandpa;

		if (!son)
			return (NULL);
		grand_son = (dir ? son->right : son->left);
		if (grand_son)
			grand_son->parent = node;
		(dir ? node->left : node->right) = grand_son;
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
			std::cout << tree->item << std::endl;
			in_order_print(tree->right);
		}
	}

#endif