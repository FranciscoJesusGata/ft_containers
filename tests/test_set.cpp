#include <tester.hpp>
#include <list>

template <typename SetType>
void	print_set(const SetType &src)
{
	for (typename SetType::const_iterator it = src.begin(), last = src.end() ; it != last ; it++)
			std::cout << *it << std::endl;
}

template <typename SetType>
void	print_set_reversed(const SetType &src)
{
	typename SetType::const_iterator it = src.end(), last = src.begin();

	it--;
	for ( ; it != last ; it--)
		std::cout << *it << std::endl;
	std::cout << *it << std::endl;
}

template <typename SetType, typename KeyType>
void	test_bounds(SetType &m, const KeyType &k) {
	typename SetType::iterator lower = m.lower_bound(k),
			 upper = m.upper_bound(k),
			 end_it = m.end();
	ft::pair<typename SetType::iterator,
		typename SetType::iterator> equal = m.equal_range(k);

	std::cout << "Using non-const set" << std::endl;
	std::cout << "Lower bound: ";
	if (lower == end_it)
		std::cout << "[ END ]" << std::endl;
	else
		std::cout << *lower << std::endl;
	std::cout << "Upper bound: ";
	if (upper == end_it)
		std::cout << "[ END ]" << std::endl;
	else
		std::cout << *upper << std::endl;
	std::cout << "Equal range: " <<  (lower == equal.first ? "OK" : "KO 💥");
	std::cout << " && " << (upper == equal.second ? "OK" : "KO 💥") << std::endl;
	std::cout << std::endl;
}

template <typename SetType, typename KeyType>
void	test_bounds_const(const SetType &m, const KeyType &k) {
	typename SetType::const_iterator lower = m.lower_bound(k),
			 upper = m.upper_bound(k),
			 end_it = m.end();
	ft::pair<typename SetType::const_iterator,
		typename SetType::const_iterator> equal = m.equal_range(k);

	std::cout << "Using non-const set" << std::endl;
	std::cout << "Lower bound: ";
	if (lower == end_it)
		std::cout << "[ END ]" << std::endl;
	else
		std::cout << *lower << std::endl;
	std::cout << "Upper bound: ";
	if (upper == end_it)
		std::cout << "[ END ]" << std::endl;
	else
		std::cout << *upper << std::endl;
	std::cout << "Equal range: " <<  (lower == equal.first ? "OK" : "KO 💥");
	std::cout << " && " << (upper == equal.second ? "OK" : "KO 💥") << std::endl;
	std::cout << std::endl;
}

template <typename Iterator>
Iterator	decrement_copy_ite(Iterator it, int n) {
	Iterator c_it(it);

	for (int i = 0 ; i <= n ; i++)
		c_it--;
	return (c_it);
}

template <typename Iterator>
Iterator	increment_copy_ite(Iterator it, int n) {
	Iterator c_it(it);

	for (int i = 0 ; i <= n ; i++)
		c_it++;
	return (c_it);
}

template <typename SetType, typename KeyType>
void	test_count(const SetType &m, const KeyType &k) {
	std::cout << "\t\tcount(" << k << ") = " << m.count(k) << std::endl;
}

template <typename SetType, typename KeyType>
void	test_find(const SetType &m, const KeyType &k) {
	typename SetType::const_iterator found = m.find(k);
	std::cout << "\t\tfind(" << k << ") = ";
	if (found == m.end())
		std::cout << "[ END ]";
	else
		std::cout << *found;
	std::cout << std::endl;
}

template <typename SetType>
void	comparison_test(const SetType &test_set, typename SetType::const_iterator &f,
			typename SetType::const_iterator &s) {
	std::cout << "\tComparing: [" << *f << "]";
	std::cout << " and  [" << *s << "]: " << std::endl;
	std::cout << "\t\tKey Compare: " << test_set.key_comp()(*f, *s) << std::endl;
	std::cout << "\t\tValue Compare: " << test_set.value_comp()(*f, *s) << std::endl;
}

template <typename SetType>
void test_cmp(SetType const &s1, SetType const &s2) {
	std::cout << std::boolalpha;	
	std::cout << "\ts1 == s2 " << (s1 == s2) << std::endl;
	std::cout << "\ts1 != s2 " << (s1 != s2) << std::endl;
	std::cout << "\ts1 < s2 " << (s1 < s2) << std::endl;
	std::cout << "\ts1 <= s2 " << (s1 <= s2) << std::endl;
	std::cout << "\ts1 > s2 " << (s1 > s2) << std::endl;
	std::cout << "\ts1 >= s2 " << (s1 >= s2) << std::endl;
	std::cout << std::noboolalpha;
	std::cout << std::endl;
}

void	test_set(void) {
	timeval start;

	gettimeofday(&start, NULL);
	std::cout << "Constructor tests:" << std::endl;
	{
		ft::set<int> original;
		for (int i = 0; i <= 30 ; i++)
			original.insert(i);
		ft::set<int>::iterator it = original.begin(), nd = original.end();
		ft::set<int> range_cpy(it, --(--nd));
		for (int i = 0 ; i < 10 ; ++i)
			original.insert(i * 5);
		ft::set<int> normal_cpy(original);
		it = original.begin();
		nd = --(--nd);
		for (int i = 0 ; i < 12 ; ++i)
			original.insert(i * 2);
		print_set(original);
		print_set(range_cpy);
		print_set(normal_cpy);
		original = normal_cpy;
		normal_cpy = range_cpy;
		range_cpy.clear();
		print_set(original);
		print_set(range_cpy);
		print_set(normal_cpy);

		std::list<int> midnight;
		
		midnight.push_back(42);
		midnight.push_back(21);
		midnight.push_back(84);
		midnight.push_back(10);
		midnight.push_back(98);
		midnight.push_back(10);
		midnight.push_back(98);
		midnight.push_back(11);
	
		ft::set<int> ohno(midnight.begin(), midnight.end());
		midnight.clear();
		print_set(ohno);
	}
	std::cout << "Bounds tests:" << std::endl;
	{
		ft::set<char> abecedario;
		for (char c = 'a';c <= 'h';c++)
			abecedario.insert(c);
		print_set(abecedario);
		test_bounds_const(abecedario, '`');
		test_bounds(abecedario, 'a');
		test_bounds_const(abecedario, 'd');
		test_bounds(abecedario, 'f');
		test_bounds_const(abecedario, 'h');
		test_bounds(abecedario, 'k');
	}
	std::cout << "Find and count tests" << std::endl;
	{
		ft::set<int> grunch;

		for (int i = 5 ; i <= 100 ; i += 5)
			grunch.insert(i);
		std::cout << "\tCount tests:" << std::endl;
		test_count(grunch, 1);
		test_count(grunch, -1);
		test_count(grunch, 20);
		test_count(grunch, 0);
		test_count(grunch, 12);
		test_count(grunch, 100);
		std::cout << "\tFind tests:" << std::endl;
		test_find(grunch, 42);
		test_find(grunch, -10);
		test_find(grunch, 0);
		test_find(grunch, 50);
		test_find(grunch, 25);
		test_find(grunch, 10);

		grunch.erase(grunch.find(10));
		print_set(grunch);
	}
	std::cout << "Capacity tests" << std::endl;
	{
		ft::set<std::string> sainte;

		sainte.insert(std::string("Alright buddy, you have two options here"));
		sainte.insert(std::string("You can be a saint"));
		sainte.insert(std::string("or you can be a Grinch"));
		sainte.insert(std::string("Those are your two choices"));
		sainte.insert(std::string("Choose wisely"));
		sainte.insert(std::string("So what's it gonna be, huh, huh?"));
		sainte.insert(std::string("fgata-va"));
		sainte.insert(std::string("F I G A T O"));
		sainte.insert(std::string("or fajita-va"));
		sainte.insert(std::string("B U R R I T O"));
		std::cout << "\tSet size:" << sainte.size() << std::endl;
		std::cout << "\tMax size:" << sainte.max_size() << std::endl;
		
		std::list<std::string> test(sainte.begin(), sainte.end());	
		
		ft::set<std::string> santa(test.begin(), test.end());
		std::cout << "\tRange constructed set size:" << santa.size() << std::endl;
		std::cout << "\tMax size:" << sainte.max_size() << std::endl;
		test.empty();
		std::cout << "\tDoes range construct make shadow copy? " << (santa.empty() ? "no" : "yes") << std::endl;
		santa.empty();
		santa = sainte;
		std::cout << "\tEqual operator copied set size:" << santa.size() << std::endl;
		std::cout << "\tMax size:" << sainte.max_size() << std::endl;
		sainte.clear();
		std::cout << "\tDoes equal operator make shadow copy? " << (santa.empty() ? "no" : "yes") << std::endl;
		
		std::cout << "\tDo what's it gonna be, huh, huh?" << std::endl;
		std::cout << "\t" << (sainte.empty() ? "grunch" : "sainte") << std::endl;
		santa.clear();
		std::cout << "\t" << (santa.empty() ? "Have I truly become a monster?" :
				"I know everything about what makes you human.") << std::endl;
	}
	std::cout << "Iterators tests:" << std::endl;
	{
		ft::set<Dummy<int> > gorlfil;

		for (int i = 0 ; i < 26 ; i++)
		{
			gorlfil.insert(Dummy<int>(i));
		}
		
		ft::set<Dummy<int> >::iterator jhon(gorlfil.begin());
		ft::set<Dummy<int> >::const_iterator odi(gorlfil.begin());
		print_set(gorlfil);

		std::cout << *(++odi) << std::endl;
		std::cout << *(odi++) << std::endl;
		std::cout << *(odi++) << std::endl;
		std::cout << *(++odi) << std::endl;

		jhon->dummyMethod();
		odi->dummyMethod();
		
		std::cout << *(++jhon) << std::endl;
		std::cout << *(jhon++) << std::endl;
		std::cout << *(jhon++) << std::endl;
		std::cout << *(++jhon) << std::endl;

		std::cout << *(--odi) << std::endl;
		std::cout << *(odi--) << std::endl;
		std::cout << *(odi--) << std::endl;
		std::cout << *(--odi) << std::endl;

		(*jhon).dummyMethod();
		(*odi).dummyMethod();
		
		std::cout << *(--jhon) << std::endl;
		std::cout << *(jhon--) << std::endl;
		std::cout << *(jhon--) << std::endl;
		std::cout << *(--jhon) << std::endl;
	}
	std::cout << "Reverse iterator tests:" << std::endl;
	{
		std::cout << "\tBase offset tests:" << std::endl;
		ft::set<char> reversed_set;
		
		for (int i = 25; i >= 0 ; i--)
			reversed_set.insert((char) (i + 'a'));

		ft::set<char>::iterator it(reversed_set.begin());
		ft::set<char>::reverse_iterator rit(it);
		ft::set<char>::reverse_iterator ritend;

		std::cout << std::boolalpha;
		std::cout << (rit.base() == it) << std::endl;
		std::cout << ((decrement_copy_ite(rit, 5)).base() == it) << std::endl;
		std::cout << ((decrement_copy_ite(rit, 1)).base() == it) << std::endl;
		--rit;
		--rit;
		std::cout << *rit.base() << std::endl;
		std::cout << *(increment_copy_ite(rit.base(), 1)) << std::endl;
		std::cout << *(decrement_copy_ite(rit, 1)).base() << std::endl;
		--rit;
		std::cout << *rit << std::endl;
		std::cout << *(rit.base()) << std::endl;
		rit = reversed_set.rbegin();
		ritend = reversed_set.rend();

		while (rit != ritend)
			std::cout << *(rit++) << std::endl;
		print_set_reversed(reversed_set);

		std::cout << std::endl << "\tDerefence tests:" << std::endl; 

		ft::set<Dummy<char> > dleifrag;

		for (int i = 0 ; i < 26 ; i++)
		{
			dleifrag.insert((char)(i + 'a'));
		}
		
		ft::set<Dummy<char> >::reverse_iterator nhoj(dleifrag.rbegin());
		ft::set<Dummy<char> >::const_reverse_iterator eido(dleifrag.rbegin());
		print_set(dleifrag);

		std::cout << *(++eido) << std::endl;
		std::cout << *(eido++) << std::endl;
		std::cout << *(eido++) << std::endl;
		std::cout << *(++eido) << std::endl;

		nhoj->dummyMethod();
		eido->dummyMethod();
		
		std::cout << *(++nhoj) << std::endl;
		std::cout << *(nhoj++) << std::endl;
		std::cout << *(nhoj++) << std::endl;
		std::cout << *(++nhoj) << std::endl;

		std::cout << *(--eido) << std::endl;
		std::cout << *(eido--) << std::endl;
		std::cout << *(eido--) << std::endl;
		std::cout << *(--eido) << std::endl;

		(*nhoj).dummyMethod();
		(*eido).dummyMethod();
		
		std::cout << *(--nhoj) << std::endl;
		std::cout << *(nhoj--) << std::endl;
		std::cout << *(nhoj--) << std::endl;
		std::cout << *(--nhoj) << std::endl;

	}
	std::cout << "Key and Value comparison tests:" << std::endl;
	{
		ft::set <char> edward;

		edward.insert('a');
		edward.insert('b');
		edward.insert('c');
		edward.insert('d');
		edward.insert('e');
		edward.insert('f');
		for (ft::set<char, int>::const_iterator first = edward.begin(); first != edward.end() ; first++)
			for (ft::set<char, int>::const_iterator second = edward.begin() ; second != edward.end() ; second++)
				comparison_test(edward, first, second);
	}
	std::cout << "Insert tests:" << std::endl;
	{
		ft::set<int> who;

		who.insert(84);	
		print_set(who);
		std::cout << std::endl;
		who.insert(84);
		print_set(who);
		std::cout << std::endl;
		who.insert(42);
		print_set(who);
		std::cout << std::endl;
		who.insert(33);
		print_set(who);
		std::cout << std::endl;
		who.insert(88);
		print_set(who);
		std::cout << std::endl;
		who.insert(21);
		print_set(who);
		std::cout << std::endl;
		who.insert(30);
		print_set(who);
		std::cout << std::endl;
		who.insert(44);
		print_set(who);
		std::cout << std::endl;
		who.insert(who.begin(), 1998);
		print_set(who);
		std::cout << std::endl;
		who.insert(who.end(), 1990);
		print_set(who);
		std::cout << std::endl;
		who.insert(who.end(), 2000);
		print_set(who);
		std::cout << std::endl;

		ft::set<int> where;
		where.insert(who.begin(), who.end());
		who.clear();
		std::list<int> when;
		when.push_back(1);
		when.push_back(2);
		when.push_back(3);
		when.push_back(4);
		when.push_back(4);
		when.push_back(5);
		when.push_back(6);
		when.push_back(7);
		when.push_back(8);
		where.insert(when.begin(), when.begin());
		print_set(where);
		std::cout << std::endl;
		where.insert(when.begin(), when.end());
		print_set(where);
		std::cout << std::endl;
	}
	{
		ft::set<std::string> hint_insert;

		hint_insert.insert("lol");
		hint_insert.insert("mdr");
		hint_insert.insert("funny");
		hint_insert.insert("bunny");
		hint_insert.insert("fizz");
		hint_insert.insert("buzz");
		hint_insert.insert(hint_insert.begin(), "fuzzy");
		hint_insert.insert(hint_insert.begin(), "beauty");
		hint_insert.insert(hint_insert.end(), "Hello");
		hint_insert.insert(hint_insert.end(), "World");
	}
	std::cout << "Erase tests: " << std::endl;
	{
		ft::set<int> tuna;
		for (int i = 1; i <= 20 ; i++)
			tuna.insert(i);
		print_set(tuna);
		std::cout << std::endl;
		tuna.erase(++tuna.begin());
		print_set(tuna);
		std::cout << std::endl;
		tuna.erase(tuna.begin());
		print_set(tuna);
		std::cout << std::endl;
		tuna.erase(--tuna.end());
		print_set(tuna);
		std::cout << std::endl;
		tuna.erase(tuna.begin(), ++(++(++tuna.begin())));
		print_set(tuna);
		std::cout << std::endl;
		tuna.erase(--(--(--tuna.end())), --tuna.end());
		print_set(tuna);
		std::cout << std::endl;
		tuna.insert(19);
		tuna.insert(20);
		print_set(tuna);
		std::cout << std::endl;
		tuna.erase(--(--(--tuna.end())), tuna.end());
		print_set(tuna);
		std::cout << std::endl;
		tuna.erase(tuna.begin(), --tuna.end());
		print_set(tuna);
		std::cout << std::endl;
		tuna.insert(16);
		tuna.insert(17);
		tuna.insert(18);
		tuna.insert(19);
		print_set(tuna);
		std::cout << std::endl;
		tuna.erase(tuna.begin(), tuna.end());
		print_set(tuna);
		std::cout << std::endl;

		ft::set<int> salmon;
		for (int i = 1 ; i <= 5 ; i++)
			salmon.insert(i);
		print_set(salmon);
		for (int i = 1 ; i <= 4 ; i++)
			salmon.erase(i);
		print_set(salmon);
		std::cout << std::endl;
		salmon.erase(*salmon.begin());
		print_set(salmon);
		std::cout << std::endl;
		salmon.erase(*(--salmon.end()));
		print_set(salmon);
		std::cout << std::endl;
		salmon.insert(24);
		salmon.insert(-5);
		salmon.insert(24);
		print_set(salmon);
		std::cout << std::endl;
		salmon.erase(4);
		print_set(salmon);
		std::cout << std::endl;
		salmon.erase(3);
		print_set(salmon);
		std::cout << std::endl;

		ft::set<int> save_me;

		save_me.insert(50);

		save_me.insert(80);
		save_me.insert(30);

		save_me.insert(25);
		save_me.insert(35);
		save_me.insert(75);
		save_me.insert(95);

		save_me.insert(11);
		save_me.insert(28);
		save_me.insert(33);
		save_me.insert(37);

		save_me.insert(70);
		save_me.insert(78);
		save_me.insert(93);
		save_me.insert(100);

		save_me.insert(5);
		save_me.insert(20);
		save_me.insert(26);
		save_me.insert(29);
		save_me.insert(32);
		save_me.insert(34);
		save_me.insert(36);
		save_me.insert(38);
		save_me.insert(60);
		save_me.insert(72);
		save_me.insert(76);
		save_me.insert(79);
		save_me.insert(85);
		save_me.insert(92);
		save_me.insert(98);
		save_me.insert(150);
		
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(30);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(95);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(29);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(92);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(26);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(85);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(25);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(90);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(20);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(11);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(28);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(50);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(38);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(37);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(36);
		print_set(save_me);
		std::cout << std::endl;
		save_me.erase(35);
		print_set(save_me);
		std::cout << std::endl;
		
	}
	std::cout << "Swap tests: " << std::endl;
	{
		ft::set<std::string> guts;
		ft::set<std::string> griffith;

		for (int i = 0; i <= 5 ; i++)
			guts.insert(std::string((i % 3) + 1, i + 'A'));
		for (int i = 6; i <= 10 ; i++)
			griffith.insert(std::string((i % 3) + 1, i + 'A'));

		ft::set<std::string>::const_iterator puck(guts.begin());
		ft::set<std::string>::const_iterator behelit(griffith.begin());
		std::cout << "\tBefore swap: " << std::endl;
		print_set(guts);
		std::cout << std::endl;
		print_set(griffith);
		std::cout << std::endl;
		guts.swap(griffith);
		std::cout << "\tAfter swap: " << std::endl;
		print_set(guts);
		std::cout << std::endl;
		print_set(griffith);
		std::cout << std::endl;
		guts.swap(griffith);
		std::cout << "\tCheck iterators reference:" << std::endl << std::boolalpha;
		std::cout << "\t\t" << (puck == guts.begin()) << std::endl;
		std::cout << "\t\t" << (behelit == griffith.begin()) << std::endl;
	}
	std::cout << "Relational operators:" << std::endl;
	{
		ft::set<char> one;
		ft::set<char> two;

		one.insert('a');
		one.insert('b');
		one.insert('c');
		one.insert('d');
		
		two.insert('a');
		two.insert('b');
		two.insert('c');
		two.insert('d');
		
		test_cmp(one, two);
		test_cmp(two, one);

		two.insert('e');
		two.insert('f');
		two.insert('g');
		two.insert('h');

		test_cmp(one, two);
		test_cmp(two, one);

		one.erase(++(++(++one.begin())));

		test_cmp(one, two);
		test_cmp(two, one);

		swap(one, two);

		test_cmp(one, two);
		test_cmp(two, one);
	}
	std::cout << "Mix tests: " << std::endl;
	{
		ft::set<char> rosalia;
		ft::set<char>::iterator hint = rosalia.insert('m').first;
		if (rosalia.count('a'))
			std::cout << "Element found" << std::endl;
		else
			std::cout << "Element not found" << std::endl;
		ft::set<char>::iterator equal_it = rosalia.insert(hint, 'm');
		std::cout << std::boolalpha << (*hint == *equal_it) << " " << rosalia.size() << std::endl;
		rosalia.insert(hint, 'n');
		rosalia.insert('b');
		rosalia.insert('c');
		rosalia.insert('z');
		rosalia.insert('b');
		rosalia.insert('c');
		rosalia.insert('d');
		rosalia.insert('e');
		rosalia.insert('u');
		rosalia.insert('s');
		rosalia.insert('f');
		rosalia.insert('g');
		rosalia.insert('i');
		rosalia.insert('h');
		rosalia.insert('w');
		rosalia.insert('j');
		rosalia.insert('p');
		rosalia.insert('q');
		rosalia.insert('r');
		rosalia.insert('o');
		rosalia.insert('t');
		rosalia.insert('v');
		rosalia.insert('x');
		rosalia.insert('y');
		print_set(rosalia);
		ft::set<char>	rowsaleah;
		rowsaleah.insert(rosalia.begin(), rosalia.end());
		for (ft::set<char>::iterator it = rosalia.begin(), last = rosalia.end(); it != last ; it++)
			std::cout << (*it) << std::endl;
		std::cout << std::endl;
		ft::set<char>::value_compare my_comp = rosalia.value_comp();
		for (ft::set<char>::iterator it = rowsaleah.begin(), last = rowsaleah.end(), other_it = rosalia.begin(); it != last ; it++, other_it++) {
			if (my_comp(*it, *other_it) != my_comp(*other_it, *it)) {
				std::cout << (*it) << " is not equal to " << (*other_it) << std::endl;
				break ;
			}
		}
		std::cout << (rosalia == rowsaleah) << std::endl;
		rosalia.insert('0');
		rowsaleah.swap(rosalia);
		std::cout << rosalia.size() << ' ';
		if (rosalia.find('0') != rosalia.end())
			std::cout << "Element found" << std::endl;
		else
			std::cout << "Element not found" << std::endl;
		std::cout << rowsaleah.size() << std::endl;
		std::cout << (rosalia == rowsaleah) << std::endl;
		ft::set<char>::iterator itlow = rosalia.lower_bound('b');
		if (itlow != rosalia.end())
			std::cout << *itlow << std::endl;
		ft::set<char>::iterator uplow = rosalia.upper_bound('d');
		if (uplow != rosalia.end())
			std::cout << *uplow << std::endl;
	}
	print_timediff("set", start);	
	std::cout << "Worst case scenario:" << std::endl;
	{
		gettimeofday(&start, NULL);
		ft::set<int> hell;
		for (size_t i = 0 ; i < 1e6 ; i++)
			hell.insert(i % 666);
		for (ft::set<int, int>::const_iterator it = hell.begin() ; it != hell.end() ; it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
		for (ft::set<int, int>::const_reverse_iterator it = hell.rbegin() ; it != hell.rend() ; it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
		print_timediff("set", start);
	}
}
