#include <RBTree.hpp>
#include <utility.hpp>
#include <algorithm.hpp>
#include <memory>
#include <iostream>

template <class T, class Compare>
class value_compare {
	protected:
		Compare comp;
	public:
  	value_compare (Compare c) : comp(c) {}
  	typedef T value_type;
  	typedef bool result_type;
  	typedef value_type first_argument_type;
	  typedef value_type second_argument_type;
  	bool operator() (const value_type& x, const value_type& y) const
  	{
  		return comp(x.first, y.first);
  	}
};


#define KEY_TYPE char
#define MAPPED_TYPE std::string
#define PAIR_TYPE ft::pair<const KEY_TYPE, MAPPED_TYPE>
#define TREE_TYPE ft::RBTree<PAIR_TYPE, value_compare<PAIR_TYPE, std::less<KEY_TYPE> >,std::less<KEY_TYPE>, std::allocator<PAIR_TYPE> >

void test_erase(TREE_TYPE::node_type *node, TREE_TYPE &tree) {
	std::cout << "Erasing " << node->item.first << std::endl << std::endl;
	tree.erase(node);
	ft::in_order_mapi(tree.root, ft::print_node);
	std::cout << "===========================" << std::endl << std::endl;
}

void test_erase(TREE_TYPE::node_type *start, TREE_TYPE::node_type *finish, TREE_TYPE &tree) {
	std::cout << "Erasing from " << start->item.first << " until " << finish->item.first << std::endl << std::endl;
	TREE_TYPE::node_type	*tmp;
	while (start != finish) {
		tmp = start;
		start = ft::next_node<PAIR_TYPE, false>(start);
		tree.erase(tmp);
	}
	ft::in_order_mapi(tree.root, ft::print_node);
	std::cout << "===========================" << std::endl << std::endl;
}

int  main(int argc, char *argv[]) {
	TREE_TYPE rosalia;

	(void)argc;
	rosalia.insert(ft::make_pair('a', "alfa, altura, alien"));
	rosalia.insert(ft::make_pair('b', "bandida"));
	rosalia.insert(ft::make_pair('c', "coqueta"));
	rosalia.insert(ft::make_pair('z', "zarzamora o de zapatea'o, o de zorra también"));
	rosalia.insert(ft::make_pair('d', "dinamita"));
	rosalia.insert(ft::make_pair('e', "expensiva, emperatriz, enigma, enterada"));
	rosalia.insert(ft::make_pair('n', "ni se te ocurra ni pensarlo"));
	rosalia.insert(ft::make_pair('u', "ultrasonidos"));
	rosalia.insert(ft::make_pair('s', "sata"));
	rosalia.insert(ft::make_pair('f', "Flux Æon"));
	rosalia.insert(ft::make_pair('g', "guapa"));
	rosalia.insert(ft::make_pair('i', "inteligencia artificial"));
	rosalia.insert(ft::make_pair('h', "hondura"));
	rosalia.insert(ft::make_pair('m', "motomami"));
	rosalia.insert(ft::make_pair('w', "Willie Colón, de Winter Fall también"));
	rosalia.insert(ft::make_pair('j', "jineta"));
	rosalia.insert(ft::make_pair('p', "patrona"));
	rosalia.insert(ft::make_pair('q', "qué reinona"));
	rosalia.insert(ft::make_pair('r', "Racineta, Racineta, rango, Racineta, rango"));
	rosalia.insert(ft::make_pair('o', "orquídea"));
	rosalia.insert(ft::make_pair('t', "titánica"));
	rosalia.insert(ft::make_pair('v', "vendetta"));
	rosalia.insert(ft::make_pair('x', "te despejo la X en un momento"));
	rosalia.insert(ft::make_pair('y', "yenes, de yantas"));	
	ft::in_order_mapi(rosalia.root, ft::print_node);
	std::cout << std::endl;
	ft::pre_order_mapi(rosalia.root, ft::print_node);
	//Delete u simple delete
	/*rosalia.erase(ft::make_pair('u', MAPPED_TYPE()));
	std::cout << "Deleting u:" << std::endl;
	ft::pre_order_mapi(rosalia.root, ft::print_node);
	std::cout << std::endl;
	ft::in_order_mapi(rosalia.root, ft::print_node);
	//Delete root delete case 1 and 4
	rosalia.erase(ft::make_pair(rosalia.root->item.first, MAPPED_TYPE()));
	std::cout << "Deleting root:" << std::endl;
	ft::pre_order_mapi(rosalia.root, ft::print_node);
	std::cout << std::endl;
	ft::in_order_mapi(rosalia.root, ft::print_node);
	//delete q, simple delete case with red son
	rosalia.erase(ft::make_pair('q', MAPPED_TYPE()));
	std::cout << "Deleting q:" << std::endl;
	ft::pre_order_mapi(rosalia.root, ft::print_node);
	std::cout << std::endl;
	ft::in_order_mapi(rosalia.root, ft::print_node);
	//delete d, delete case 4
	rosalia.erase(ft::make_pair('d', MAPPED_TYPE()));
	std::cout << "Deleting d:" << std::endl;
	ft::pre_order_mapi(rosalia.root, ft::print_node);
	std::cout << std::endl;
	ft::in_order_mapi(rosalia.root, ft::print_node);
	//delete p, delete case 6
	rosalia.erase(ft::make_pair('p', MAPPED_TYPE()));
	std::cout << "Deleting p:" << std::endl;
	ft::pre_order_mapi(rosalia.root, ft::print_node);
	std::cout << std::endl;
	ft::in_order_mapi(rosalia.root, ft::print_node);
	//delete i, delete case 5 and 6
	rosalia.erase(ft::make_pair('i', MAPPED_TYPE()));
	std::cout << "Deleting i:" << std::endl;
	ft::pre_order_mapi(rosalia.root, ft::print_node);
	std::cout << std::endl;
	ft::in_order_mapi(rosalia.root, ft::print_node);
	rosalia.erase(ft::make_pair('b', MAPPED_TYPE()));
	std::cout << "Deleting b:" << std::endl;
	ft::pre_order_mapi(rosalia.root, ft::print_node);
	std::cout << std::endl;
	ft::in_order_mapi(rosalia.root, ft::print_node);
	TREE_TYPE	lemon_tree;

	lemon_tree.insert(ft::make_pair('0', " * [ d A - ^ 0 1 d ! ] * "));
	lemon_tree.erase(ft::make_pair('0', MAPPED_TYPE()));
	std::cout << std::endl << "== ERASE ELEMENT ONE BY ONE ==" << std::endl << std::endl;
	for (unsigned int i = 0; i < 10; ++i)
  	lemon_tree.insert(ft::make_pair(i + 48, std::string((10 - i), i + 65)));
	ft::in_order_mapi(lemon_tree.root, ft::print_node);
	test_erase(ft::next_node<PAIR_TYPE, false>(lemon_tree.min()), lemon_tree);
	test_erase(lemon_tree.min(), lemon_tree);
	test_erase(lemon_tree.max(), lemon_tree);
	test_erase(lemon_tree.min(), lemon_tree.search(ft::make_pair('5', MAPPED_TYPE())), lemon_tree);
	test_erase(ft::next_node<PAIR_TYPE, false>(lemon_tree.min()), lemon_tree.max(), lemon_tree);*/
	system((std::string("leaks -q ") += argv[0] + 2).c_str());
	std::cout << std::endl;
	return (0);
}
