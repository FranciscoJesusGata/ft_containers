/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:48:51 by fgata-va          #+#    #+#             */
/*   Updated: 2022/09/16 18:40:22 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <iostream>
# include <utility.hpp>
# include <type_traits.hpp>

namespace ft {
	enum	e_color {BLACK, RED};
	enum	e_dir {LEFT, RIGHT};

	template <class T>
	struct RBTreeNode
	{
		struct RBTreeNode	*parent;
		struct RBTreeNode	*left;
		struct RBTreeNode	*right;
		bool				nil;
		e_color				color;
		T					item;

		RBTreeNode (): left(NULL), right(NULL), nil(false), color(RED), item() {}
		RBTreeNode (const T &item): left(NULL), right(NULL), nil(false), color(RED), item(item) {}
		~RBTreeNode () {}
		RBTreeNode	&operator=(const RBTreeNode &src) {
			parent = src.parent;
			left = src.left;
			right = src.right;
			item = src.item;
			color = src.color;
			nil = src.nil;
			return (*this);
		} 
	};

# define NODE typename ft::conditional<Const, const ft::RBTreeNode<T>, ft::RBTreeNode<T> >::type

	template <class T, bool Const>
	NODE	*next_node(NODE *src) {
		NODE *node = src;

		if (!node->nil) {
			if (!node->right->nil) {
				node = node->right;
				while (!node->left->nil)
					node = node->left;
			}
			else {
				while (!node->parent->nil && node == node->parent->right)
					node = node->parent;
				node = node->parent;
			}
		}
		else
			node = node->left;
		return (node);
	}

	template <class T, bool Const>
	NODE	*prev_node(NODE *src) {
		NODE	*node = src;

		if (!node->nil) {
			if (!node->left->nil) {
				node = node->left;
				while (!node->right->nil)
					node = node->right;
			}
			else {
				while (node->parent && node == node->parent->left)
					node = node->parent;
				node = node->parent;
			}
		}
		else
			node = node->right;
		return (node);
	}

	template < class T, class Compare, class KeyComp, class Alloc>
	struct RBTree
	{
		typedef RBTreeNode<T>					node_type;
		typedef	T											value_type;
		node_type											*root;
		Compare												cmp;
		typename Alloc::template rebind<node_type>::other	node_allocator;

		RBTree(const Alloc &alloc = Alloc(), const Compare &comp = Compare(KeyComp())): cmp(comp), node_allocator(alloc), nil() {
			nil = node_allocator.allocate(sizeof(node_type));
			node_allocator.construct(nil, value_type());
			nil->left = nil;
			nil->right = nil;
			nil->parent = nil;
			nil->nil = true;
			root = nil;
		}

		~RBTree() { delete_tree(root); destroy_node(nil); }

		ft::pair<node_type*,bool>	insert(const value_type &item) {
			return (insert(item, root));
		}

		ft::pair<node_type*,bool>	insert(const value_type &item, node_type *start) {
			node_type	*parent = nil;
			node_type	*new_node;

			if (start != root && !(hint_checker(item, start)))
				start = root;
			while (start != nil)
			{
				parent = start;
				if (cmp(item, start->item))
					start = start->left;
				else if (cmp(start->item, item))
					start = start->right;
				else
					return (ft::make_pair<node_type*,bool>(start, false));
			}
			new_node = create_node(item);
			new_node->parent = parent;
			if (parent == nil) {
				root = new_node;
				nil->parent = new_node;
				nil->left = new_node;
				nil->right = new_node;
			}
			else if (cmp(new_node->item, parent->item)) {
				parent->left = new_node;
				if (parent == nil->left)
					nil->left = new_node;
			}
			else {
				parent->right = new_node;
				if (parent == nil->right)
					nil->right = new_node;
			}
			insert_fixup(new_node);
			return (ft::make_pair<node_type*,bool>(new_node,true));
		}

		void		erase(const T &item) {
			node_type *node;
			node_type	*sustitute;

			node = search(item);
			if (node != nil) {
				/*
				 * If the element is found, then we will check if the element is a leaf or has a right child
				 * so the first we wanna know is if there is left child, then we wanna know if there is right or none child.
				 * In case there is a left child, we will take the immediately lower element, swap the value and delete it.
				 * In case there is only a right child, we will take the immediately higher element, swap the value and delete it.
				 * If there is none child, the element will be deleted.
				 */
				if (node->left != nil) {
					sustitute = prev_node<T, false>(node);
					swap_node(node, sustitute);
					node->color = sustitute->color;
				}
				else if (node->right != nil) {
					sustitute = next_node<T, false>(node);
					swap_node(node, sustitute);
					node->color = sustitute->color;
					if (root == node)
						root = sustitute;
				}
				if (node == root)
					root = nil;
				else
					(node->parent->left == node ? node->parent->left : node->parent->right) = nil;
				destroy_node(node);
				//after the deletion we will need to rebalance the tree
			}
		}

		node_type	*search(const T &item) const {
			node_type	*node = root;
			
			while (node != nil)
			{
				if (cmp(node->item, item))
					node = node->right;
				else if (cmp(item, node->item))
					node = node->left;
				else
					break ;
			}
			return (node);
		}

		node_type	*rotate(node_type *node, int dir) {
			node_type	*son = (dir ? node->left : node->right);
			node_type	*grandson;
			node_type	*grandpa;

			if (son == nil)
				return (NULL);
			grandson = (dir ? son->right : son->left);
			if (grandson != nil)
				grandson->parent = node;
			(dir ? node->left : node->right) = grandson;
			(dir ? son->right : son->left) = node;
			grandpa = node->parent;
			son->parent = grandpa;
			node->parent = son;
			if (grandpa != nil)
				(node == grandpa->right ? grandpa->right : grandpa->left) = son;
			else
				root = son;
			return (son);
		}

		void	swap(RBTree	&lhs) {
			node_type *aux;
			node_type *nil_aux;

			aux = lhs.root;
			lhs.root = root;
			root = aux;
			nil_aux = lhs.nil;
			lhs.nil = nil;
			nil = nil_aux;
		}

		void	clear(void) {
			delete_tree(root);
			root = nil;
			nil->left = nil;
			nil->right = nil;
			nil->parent = nil;
		}

		size_t		max_size(void) const {
			return (node_allocator.max_size());
		}

		void	in_order_mapi(node_type *tree, void (*f)(node_type *)) {
			if (tree != nil)
			{
				in_order_mapi(tree->left, f);
				f(tree);
				in_order_mapi(tree->right, f);
			}
		}
		
		void	pre_order_mapi(node_type *tree, void (*f)(node_type *)) {
			if (tree != nil)
			{
				f(tree);
				pre_order_mapi(tree->left, f);
				pre_order_mapi(tree->right, f);
			}
		}

		node_type	*min() {
			return (nil->left);
		}
		
		node_type	*min() const {
			return (nil->left);
		}

		node_type	*max() {
			return (nil->right);
		}

		node_type	*max() const {
			return (nil->right);
		}

		private:

		node_type					*nil;

		void	insert_fixup(node_type *new_node)
		{
			node_type *parent = new_node->parent;
			node_type *uncle;
			node_type *grandpa;

			while (parent != nil && parent->color == RED)
			{
				uncle = (parent == parent->parent->left ? parent->parent->right : parent->parent->left);
				if (uncle != nil && uncle->color == RED) {
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
			node->left = nil;
			node->right = nil;
			node->parent = nil;
			return (node);
		}

		void		destroy_node(node_type *node) {
			node_allocator.destroy(node);
			node_allocator.deallocate(node, sizeof(node_type));
		}

		void		delete_tree(node_type *tree) {
			if (tree != nil)
			{
				delete_tree(tree->left);
				delete_tree(tree->right);
				destroy_node(tree);
				tree = NULL;
			}
		}

		bool		hint_checker(const value_type &item, node_type *start) const
		{
			if (start == nil)
					return (false);
			for (node_type *p = start->parent ; p != nil ; p = p->parent) {
				if (cmp(p->item, p->parent->item) != cmp(item, p->parent->item)
					|| (!p->parent && p->parent != root)) {
					return (false);
				}
			}
			return (true);
		}

		void		swap_node(node_type *a, node_type *b) {
			node_type *aux;

			if (a == root)
				root = b;
			else {
				(a == a->parent->left ? a->parent->left : a->parent->right) = b;
				if (b == root)
					root = a;
				else
					(b == b->parent->left ? b->parent->left : b->parent->right) = a;
			}
			aux = a->left;
			a->left = b->left;
			b->left = aux;
			aux = a->right;
			a->right = b->right;
			b->right = aux;
			aux = a->parent;
			a->parent = b->parent;
			b->parent = aux;

		}
	};

	template <class T>
	void	print_node(RBTreeNode<T> *tree) {	
		std::cout << "[ "<< (tree->color ? "RED" : "BLACK") << " ]";
		std::cout << ": [" << tree->item.first << " => " << tree->item.second << "]" << std::endl;
	}

	template <class T>
	void	in_order_mapi(RBTreeNode<T> *tree, void (*f)(RBTreeNode<T> *)) {
		if (!tree->nil)
		{
			in_order_mapi(tree->left, f);
			f(tree);
			in_order_mapi(tree->right, f);
		}
	}

	template <class T>
	void	pre_order_mapi(RBTreeNode<T> *tree, void (*f)(RBTreeNode<T> *)) {
		if (!tree->nil)
		{
			f(tree);
			pre_order_mapi(tree->left, f);
			pre_order_mapi(tree->right, f);
		}
	}
};

#endif
