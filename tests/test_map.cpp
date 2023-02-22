#include <tester.hpp>
#include <list>

template <typename PairType>
void	print_pair(const PairType &src)
{
	std::cout << "First: " << src.first << ", Second: " << src.second << "." << std::endl;
}

template <typename MapType>
void	print_map(const MapType &src)
{
	for (typename MapType::const_iterator it = src.begin(), last = src.end() ; it != last ; it++)
			std::cout << "['" << it->first << "']" << "=> \"" << it->second << '"' << std::endl;
}

template <typename MapType>
void	print_map_reversed(const MapType &src)
{
	typename MapType::const_iterator it = src.end(), last = src.begin();

	it--;
	for ( ; it != last ; it--)
			std::cout << "['" << it->first << "']" << "=> \"" << it->second << '"' << std::endl;
	std::cout << "['" << it->first << "']" << "=> \"" << it->second << '"' << std::endl;
}

template <typename MapType>
void	special_print_map(const MapType &src, const std::string separator)
{
	for (typename MapType::const_iterator it = src.begin(), last = src.end() ; it != last ; it++)
		std::cout << it->first << separator << it->second << std::endl;
}

template <typename MapType, typename KeyType>
void	test_bounds(MapType &m, const KeyType &k) {
	typename MapType::iterator lower = m.lower_bound(k),
			 upper = m.upper_bound(k),
			 end_it = m.end();
	ft::pair<typename MapType::iterator,
		typename MapType::iterator> equal = m.equal_range(k);

	std::cout << "Using non-const map" << std::endl;
	std::cout << "Lower bound: ";
	if (lower == end_it)
		std::cout << "[ END ]" << std::endl;
	else
		std::cout << lower->first << std::endl;
	std::cout << "Upper bound: ";
	if (upper == end_it)
		std::cout << "[ END ]" << std::endl;
	else
		std::cout << upper->first << std::endl;
	std::cout << "Equal range: " <<  (lower == equal.first ? "OK" : equal.first->second);
	std::cout << " && " << (upper == equal.second ? "OK" : equal.second->second) << std::endl;
	std::cout << std::endl;
}

template <typename MapType, typename KeyType>
void	test_bounds_const(const MapType &m, const KeyType &k) {
	typename MapType::const_iterator lower = m.lower_bound(k),
			 upper = m.upper_bound(k),
			 end_it = m.end();
	ft::pair<typename MapType::const_iterator,
		typename MapType::const_iterator> equal = m.equal_range(k);

	std::cout << "Using const map" << std::endl;
	if (lower == end_it)
		std::cout << "[ END ]" << std::endl;
	else
		std::cout << lower->first << std::endl;
	std::cout << "Upper bound: ";
	if (upper == end_it)
		std::cout << "[ END ]" << std::endl;
	else
		std::cout << upper->first << std::endl;
	std::cout << "Equal range: " <<  (lower == equal.first ? "OK" : equal.first->second);
	std::cout << " && " << (upper == equal.second ? "OK" : equal.second->second) << std::endl;
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

template <typename MapType, typename KeyType>
void	test_count(const MapType &m, const KeyType &k) {
	std::cout << "\t\tcount(" << k << ") = " << m.count(k) << std::endl;
}

template <typename MapType, typename KeyType>
void	test_find(const MapType &m, const KeyType &k) {
	typename MapType::const_iterator found = m.find(k);
	std::cout << "\t\tfind(" << k << ") = ";
	if (found == m.end())
		std::cout << "[ END ]";
	else
		print_pair(*found);
	std::cout << std::endl;
}

template <typename MapType>
void	comparison_test(const MapType &test_map, typename MapType::const_iterator &f,
			typename MapType::const_iterator &s) {
	std::cout << "\tComparing: [" << f->first << ", " << f->second << "]";
	std::cout << " and  [" << s->first << ", " << s->second << "]: " << std::endl;
	std::cout << "\t\tKey Compare: " << test_map.key_comp()(f->first, s->first) << std::endl;
	std::cout << "\t\tValue Compare: " << test_map.value_comp()(*f, *s) << std::endl;
}

void	test_map(void) {
	std::cout << "Constructor tests:" << std::endl;
	{
		typedef ft::map<int, std::string> map_type;
		typedef map_type::value_type pair_type;
		map_type original;
		for (int i = 0; i <= 30 ; i++)
			original[i] = std::string(i + 1, (i % 26) + 'a');

		map_type::iterator it = original.begin(), nd = original.end();
		map_type range_cpy(it, --(--nd));
		for (int i = 0 ; it != nd ; ++it) {
			it->second = std::string(i, i * 2 % 26 + 'a');
			i++;
		}
		map_type normal_cpy(original);
		it = original.begin();
		nd = --(--nd);
		for (int i = 0 ; it != nd ; ++it) {
			it->second = std::string(i + 1, i * 5 % 26 + 'a');
			i++;
		}
		print_map(original);
		print_map(range_cpy);
		print_map(normal_cpy);
		original = normal_cpy;
		normal_cpy = range_cpy;
		range_cpy.clear();
		print_map(original);
		print_map(range_cpy);
		print_map(normal_cpy);

		std::list<pair_type> midnight;
		
		midnight.push_back(pair_type(42, "The answer"));
		midnight.push_back(pair_type(21, "whut"));
		midnight.push_back(pair_type(84, "bunny"));
		midnight.push_back(pair_type(10, "funny"));
		midnight.push_back(pair_type(98, "dummy"));
		midnight.push_back(pair_type(10, "oh no"));
		midnight.push_back(pair_type(98, "this is bad"));
		midnight.push_back(pair_type(11, "i should go home now"));
	
		map_type ohno(midnight.begin(), midnight.end());
		midnight.clear();
		print_map(ohno);
	}
	std::cout << "Bounds tests:" << std::endl;
	{
		ft::map<char, std::string> abecedario;
		for (char c = 'a';c <= 'h';c++)
			abecedario[c] = std::string(((int)c % 3) + 1, c);
		print_map(abecedario);
		test_bounds_const(abecedario, '`');
		test_bounds(abecedario, 'a');
		test_bounds_const(abecedario, 'd');
		test_bounds(abecedario, 'f');
		test_bounds_const(abecedario, 'h');
		test_bounds(abecedario, 'k');
	}
	std::cout << "Find and count tests" << std::endl;
	{
		ft::map<int, std::string> grunch;

		for (int i = 5, j = 'a' ; i <= 100 ; i += 5) {
			grunch[i] = std::string((i % 5) + 1, (char) j++);
		}
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

		grunch.find(10)->second = "bruh";
		print_map(grunch);
	}
	std::cout << "Capacity tests" << std::endl;
	{
		ft::map<int, std::string> sainte;

		sainte.insert(ft::pair<int, std::string>(1, "Alright buddy, you have two options here"));
		sainte.insert(ft::pair<int, std::string>(2, "You can be a saint"));
		sainte.insert(ft::pair<int, std::string>(3, "or you can be a Grinch"));
		sainte.insert(ft::pair<int, std::string>(6, "Those are your two choices"));
		sainte.insert(ft::pair<int, std::string>(7, "Choose wisely"));
		sainte.insert(ft::pair<int, std::string>(12, "So what's it gonna be, huh, huh?"));
		sainte.insert(ft::pair<int, std::string>(14, "fgata-va"));
		sainte.insert(ft::pair<int, std::string>(21, "F I G A T O"));
		sainte.insert(ft::pair<int, std::string>(42, "or fajita-va"));
		sainte.insert(ft::pair<int, std::string>(84, "B U R R I T O"));
		std::cout << "\tMap size:" << sainte.size() << std::endl;
		std::cout << "\tMax size:" << sainte.max_size() << std::endl;
		
		std::list<ft::pair<int, std::string> > test(sainte.begin(), sainte.end());	
		
		ft::map<int, std::string> santa(test.begin(), test.end());
		std::cout << "\tRange constructed map size:" << santa.size() << std::endl;
		std::cout << "\tMax size:" << sainte.max_size() << std::endl;
		test.empty();
		std::cout << "\tDoes range construct make shadow copy? " << (santa.empty() ? "no" : "yes") << std::endl;
		santa.empty();
		santa = sainte;
		std::cout << "\tEqual operator copied map size:" << santa.size() << std::endl;
		std::cout << "\tMax size:" << sainte.max_size() << std::endl;
		sainte.clear();
		std::cout << "\tDoes equal operator make shadow copy? " << (santa.empty() ? "no" : "yes") << std::endl;
		
		std::cout << "\tDo what's it gonna be, huh, huh?" << std::endl;
		std::cout << "\t" << (sainte.empty() ? "grunch" : "sainte") << std::endl;
		santa.clear();
		std::cout << "\t" << (santa.empty() ? "Have I truly become a monster?" :
				"I know everything about what makes you human.") << std::endl;
	}
	std::cout << "Brackets operator tests: " << std::endl;
	{
		ft::map<char, std::string> maprio;

		maprio['M'] = "It's a me Mario!";
		maprio['L'] = "Mama Luigi";
		maprio['W'] = "* FARTS *";
		maprio['l'] = "Wa!";
		maprio['L'] = maprio['l'];
		maprio['l'] = "Here we go!";

		std::cout << "\tMap size: " << maprio.size() << std::endl;
		print_map(maprio);

		std::cout << "\tDoing an insert by using the [] operator" << maprio['G'] << std::endl;

		std::cout << "\tMap size: " << maprio.size() << std::endl;
		print_map(maprio);
	}
	std::cout << "Iterators tests:" << std::endl;
	{
		ft::map<char, Dummy<int> > gorlfil;

		for (int i = 0 ; i < 26 ; i++)
		{
			gorlfil[(i + 'a')] = i;
		}
		
		ft::map<char, Dummy<int> >::iterator jhon(gorlfil.begin());
		ft::map<char, Dummy<int> >::const_iterator odi(gorlfil.begin());
		print_map(gorlfil);

		print_pair(*(++odi));
		print_pair(*(odi++));
		print_pair(*(odi++));
		print_pair(*(++odi));

		jhon->second.dummyMethod();
		odi->second.dummyMethod();
		
		print_pair(*(++jhon));
		print_pair(*(jhon++));
		print_pair(*(jhon++));
		print_pair(*(++jhon));

		print_pair(*(--odi));
		print_pair(*(odi--));
		print_pair(*(odi--));
		print_pair(*(--odi));

		(*jhon).second.dummyMethod();
		(*odi).second.dummyMethod();
		
		print_pair(*(--jhon));
		print_pair(*(jhon--));
		print_pair(*(jhon--));
		print_pair(*(--jhon));
	}
	std::cout << "Reverse iterator tests:" << std::endl;
	{
		std::cout << "\tBase offset tests:" << std::endl;
		ft::map<int, char> reversed_map;
		
		for (int i = 25, j = 0; i >= 0 ; i--)
			reversed_map[j++] = (char) (i + 'a');

		ft::map<int, char>::iterator it(reversed_map.begin());
		ft::map<int, char>::reverse_iterator rit(it);
		ft::map<int, char>::reverse_iterator ritend;

		std::cout << std::boolalpha;
		std::cout << (rit.base() == it) << std::endl;
		std::cout << ((decrement_copy_ite(rit, 5)).base() == it) << std::endl;
		std::cout << ((decrement_copy_ite(rit, 1)).base() == it) << std::endl;
		--rit;
		--rit;
		print_pair(*rit.base());
		print_pair(*(increment_copy_ite(rit.base(), 1)));
		print_pair(*(decrement_copy_ite(rit, 1)).base());
		--rit;
		print_pair(*rit);
		print_pair(*(rit.base()));
		rit = reversed_map.rbegin();
		ritend = reversed_map.rend();

		while (rit != ritend)
			print_pair(*(rit++));
		print_map_reversed(reversed_map);

		std::cout << std::endl << "\tDerefence tests:" << std::endl; 

		ft::map<char, Dummy<int> > dleifrag;

		for (int i = 0 ; i < 26 ; i++)
		{
			dleifrag[(i + 'a')] = i;
		}
		
		ft::map<char, Dummy<int> >::reverse_iterator nhoj(dleifrag.rbegin());
		ft::map<char, Dummy<int> >::const_reverse_iterator eido(dleifrag.rbegin());
		print_map(dleifrag);

		print_pair(*(++eido));
		print_pair(*(eido++));
		print_pair(*(eido++));
		print_pair(*(++eido));

		nhoj->second.dummyMethod();
		eido->second.dummyMethod();
		
		print_pair(*(++nhoj));
		print_pair(*(nhoj++));
		print_pair(*(nhoj++));
		print_pair(*(++nhoj));

		print_pair(*(--eido));
		print_pair(*(eido--));
		print_pair(*(eido--));
		print_pair(*(--eido));

		(*nhoj).second.dummyMethod();
		(*eido).second.dummyMethod();
		
		print_pair(*(--nhoj));
		print_pair(*(nhoj--));
		print_pair(*(nhoj--));
		print_pair(*(--nhoj));

	}
	std::cout << "Key and Value comparison tests:" << std::endl;
	{
		ft::map <char, int> edward;

		edward['a'] = 42;
		edward['b'] = 21;
		edward['c'] = 84;
		edward['d'] = 2;
		edward['e'] = 1;
		edward['f'] = 4;
		for (ft::map<char, int>::const_iterator first = edward.begin(); first != edward.end() ; first++)
			for (ft::map<char, int>::const_iterator second = edward.begin() ; second != edward.end() ; second++)
				comparison_test(edward, first, second);
	}
	std::cout << "Insert tests:" << std::endl;
	{
		ft::map<int, std::string> who;

		who.insert(ft::pair<int, std::string>(84, "kewk"));	
		print_map(who);
		std::cout << std::endl;
		who.insert(ft::pair<int, std::string>(84, "beaaaaaaaaans"));
		print_map(who);
		std::cout << std::endl;
		who.insert(ft::pair<int, std::string>(42, "marvin"));
		print_map(who);
		std::cout << std::endl;
		who.insert(ft::pair<int, std::string>(33, "✌️ "));
		print_map(who);
		std::cout << std::endl;
		who.insert(ft::pair<int, std::string>(88, "hold up"));
		print_map(who);
		std::cout << std::endl;
		who.insert(ft::pair<int, std::string>(21, "sussy baka"));
		print_map(who);
		std::cout << std::endl;
		who.insert(ft::pair<int, std::string>(30, "aaaaAAAAAAAA"));
		print_map(who);
		std::cout << std::endl;
		who.insert(who.begin(), ft::pair<int, std::string>(44, "roses are red"));
		print_map(who);
		std::cout << std::endl;
		who.insert(who.end(), ft::pair<int, std::string>(1998, "great year"));
		print_map(who);
		std::cout << std::endl;
		who.insert(who.end(), ft::pair<int, std::string>(1990, "great decade"));
		print_map(who);
		std::cout << std::endl;

		ft::map<int, std::string> where;
		where.insert(who.begin(), who.end());
		who.clear();
		std::list<ft::pair<int, std::string> > when;
		when.push_back(ft::pair<int, std::string>(1,"oh hey"));
		when.push_back(ft::pair<int, std::string>(2,"yeah... it's late"));
		when.push_back(ft::pair<int, std::string>(3,"you are right"));
		when.push_back(ft::pair<int, std::string>(4,"but I have to finish this, alright?"));
		when.push_back(ft::pair<int, std::string>(4,"yeah I'm going home"));
		when.push_back(ft::pair<int, std::string>(5,"don't worry I'll leave soon"));
		when.push_back(ft::pair<int, std::string>(6,"who are you anyway"));
		when.push_back(ft::pair<int, std::string>(7,"no, I don't know you"));
		when.push_back(ft::pair<int, std::string>(8,"it's me speaking to myself... how bizarre"));
		where.insert(when.begin(), when.begin());
		print_map(where);
		std::cout << std::endl;
		where.insert(when.begin(), when.end());
		print_map(where);
		std::cout << std::endl;
	}
	std::cout << "Erase tests: " << std::endl;
	{
		ft::map<int, std::string> tuna;
		for (int i = 0; i <= 20 ; i++)
			tuna[i] = std::string(i + 1, (i % 26) + 'A');
		print_map(tuna);
		std::cout << std::endl;
		tuna.erase(++tuna.begin());
		print_map(tuna);
		std::cout << std::endl;
		tuna.erase(tuna.begin());
		print_map(tuna);
		std::cout << std::endl;
		tuna.erase(--tuna.end());
		print_map(tuna);
		std::cout << std::endl;
		tuna.erase(tuna.begin(), ++(++(++tuna.begin())));
		print_map(tuna);
		std::cout << std::endl;
		tuna.erase(--(--(--tuna.end())), --tuna.end());
		print_map(tuna);
		std::cout << std::endl;
		tuna[19] = "mmmm tuna";
		tuna[20] = "I'm hungry";
		print_map(tuna);
		std::cout << std::endl;
		tuna.erase(--(--(--tuna.end())), tuna.end());
		print_map(tuna);
		std::cout << std::endl;
		tuna.erase(tuna.begin(), --tuna.end());
		print_map(tuna);
		std::cout << std::endl;
		tuna[16] = "hello";
		tuna[17] = "hola";
		tuna[18] = "salut";
		tuna[19] = "hallo";
		print_map(tuna);
		std::cout << std::endl;
		tuna.erase(tuna.begin(), tuna.end());
		print_map(tuna);
		std::cout << std::endl;

		ft::map<int, std::string> salmon;
		for (int i = 0 ; i <= 5 ; i++)
			salmon[i] = std::string(i + 1, (i % 26) + 'A');
		print_map(salmon);
		for (int i = 1 ; i <= 4 ; i++)
			salmon.erase(i);
		print_map(salmon);
		std::cout << std::endl;
		salmon.erase(salmon.begin()->first);
		print_map(salmon);
		std::cout << std::endl;
		salmon.erase((--salmon.end())->first);
		print_map(salmon);
		std::cout << std::endl;
		salmon[24] = "Hours I spent programming today";
		salmon[-5] = "Hours that I spent sleeping";
		salmon[24] = "Years old when I wrote this code";
		print_map(salmon);
		std::cout << std::endl;
		salmon.erase(4);
		print_map(salmon);
		std::cout << std::endl;
		salmon.erase(3);
		print_map(salmon);
		std::cout << std::endl;

		ft::map<int, std::string> save_me;

		save_me[50] = "Top of them all";

		save_me[80] = "Right";
		save_me[30] = "Left";

		save_me[25] = "🌯";
		save_me[35] = "🥪";
		save_me[75] = "🥙";
		save_me[95] = "🌮";

		save_me[11] = "🎧";
		save_me[28] = "🎸";
		save_me[33] = "🎹";
		save_me[37] = "🥁";

		save_me[70] = "🎺";
		save_me[78] = "🎷";
		save_me[93] = "🎻";
		save_me[100] = "🎼";

		save_me[5] = "👀";
		save_me[20] = "👓";
		save_me[26] = "🤓";
		save_me[29] = "😎";
		save_me[32] = "😁";
		save_me[34] = "🦷";
		save_me[36] = "😬";
		save_me[38] = "🥶";
		save_me[60] = "😇";
		save_me[72] = "😈";
		save_me[76] = "👿";
		save_me[79] = "👹";
		save_me[85] = "💤";
		save_me[92] = "😴";
		save_me[98] = "🥱";
		save_me[150] = "🛌";
		
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(30);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(95);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(29);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(92);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(26);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(85);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(25);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(90);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(20);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(11);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(28);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(50);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(38);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(37);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(36);
		print_map(save_me);
		std::cout << std::endl;
		save_me.erase(35);
		print_map(save_me);
		std::cout << std::endl;
		
	}
	std::cout << "Swap tests: " << std::endl;
	{
		ft::map<int, std::string> guts;
		ft::map<int, std::string> griffith;

		for (int i = 0; i <= 5 ; i++)
			guts[i] = std::string((i % 3) + 1, i + 'A');
		for (int i = 6; i <= 10 ; i++)
			griffith[i] = std::string((i % 3) + 1, i + 'A');

		ft::map<int, std::string>::const_iterator puck(guts.begin());
		ft::map<int, std::string>::const_iterator behelit(griffith.begin());
		std::cout << "\tBefore swap: " << std::endl;
		print_map(guts);
		std::cout << std::endl;
		print_map(griffith);
		std::cout << std::endl;
		guts.swap(griffith);
		std::cout << "\tAfter swap: " << std::endl;
		print_map(guts);
		std::cout << std::endl;
		print_map(griffith);
		std::cout << std::endl;
		guts.swap(griffith);
		std::cout << "\tCheck iterators reference:" << std::endl << std::boolalpha;
		std::cout << "\t\t" << (puck == guts.begin()) << std::endl;
		std::cout << "\t\t" << (behelit == griffith.begin()) << std::endl;
	}
	std::cout << "Mix tests: " << std::endl;
	{
		ft::map<char, std::string> rosalia;
		ft::map<char, std::string>::iterator hint = rosalia.insert(ft::make_pair<char, std::string>('m', "motomami")).first;
		if (rosalia.count('a'))
			std::cout << rosalia['a'] << std::endl;
		else
			std::cout << "Element not found" << std::endl;
		rosalia['a'] = "test";
		std::cout << rosalia['a'] << std::endl;
		rosalia['a'] = "alfa, altura, alien";
		std::cout << rosalia['a'] << std::endl;
		ft::map<char, std::string>::iterator equal_it = rosalia.insert(hint, ft::make_pair<char, std::string>('m', "motomami"));
		std::cout << std::boolalpha << (*hint == *equal_it) << " " << rosalia.size() << std::endl;
		rosalia.insert(hint, ft::make_pair('n', "ni se te ocurra ni pensarlo"));
		rosalia.insert(ft::make_pair('b', "bandida"));
		rosalia.insert(ft::make_pair('c', "coqueta"));
		rosalia.insert(ft::make_pair('z', "zarzamora o de zapatea'o, o de zorra también"));
		rosalia.insert(ft::make_pair('b', "bandida"));
		rosalia.insert(ft::make_pair('c', "coqueta"));
		rosalia.insert(ft::make_pair('d', "dinamita"));
		rosalia.insert(ft::make_pair('e', "expensiva, emperatriz, enigma, enterada"));
		rosalia.insert(ft::make_pair('u', "ultrasonidos"));
		rosalia.insert(ft::make_pair('s', "sata"));
		rosalia.insert(ft::make_pair('f', "Flux Æon"));
		rosalia.insert(ft::make_pair('g', "guapa"));
		rosalia.insert(ft::make_pair('i', "inteligencia artificial"));
		rosalia.insert(ft::make_pair('h', "hondura"));
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
		special_print_map(rosalia, " de ");
		ft::map<char, std::string>	rowsaleah;
		rowsaleah.insert(rosalia.begin(), rosalia.end());
		for (ft::map<char, std::string>::iterator it = rosalia.begin(), last = rosalia.end(); it != last ; it++)
			std::cout << (*it).first << " de " << (*it).second << std::endl;
		std::cout << std::endl;
		ft::map<char, std::string>::value_compare my_comp = rosalia.value_comp();
		for (ft::map<char, std::string>::iterator it = rowsaleah.begin(), last = rowsaleah.end(), other_it = rosalia.begin(); it != last ; it++, other_it++) {
			if (my_comp(*it, *other_it) != my_comp(*other_it, *it)) {
				std::cout << "['" << (*it).first << "'] => " << (*it).second << " is not equal to " << "['" << (*other_it).first << "'] => " << (*other_it).second << std::endl;
				break ;
			}
		}
		std::cout << (rosalia == rowsaleah) << std::endl;
		rosalia.insert(ft::make_pair('0', "[ * t H 3 ~ ^ 0 i D * ]"));
		rowsaleah.swap(rosalia);
		std::cout << rosalia.size() << ' ';
		if (rosalia.find('0') != rosalia.end())
			std::cout << rosalia['0'] << std::endl;
		else
			std::cout << "Element not found" << std::endl;
		std::cout << rowsaleah.size() << " " << rowsaleah['0'] << std::endl;
		std::cout << (rosalia == rowsaleah) << std::endl;
		ft::map<char, std::string>::iterator itlow = rosalia.lower_bound('b');
		if (itlow != rosalia.end())
			std::cout << "['" << (*itlow).first << "']" << " => \"" << (*itlow).second << '"' << std::endl;
		ft::map<char, std::string>::iterator uplow = rosalia.upper_bound('d');
		if (uplow != rosalia.end())
			std::cout << "['" << (*uplow).first << "']" << " => \"" << (*uplow).second << '"' << std::endl;
	}
}
