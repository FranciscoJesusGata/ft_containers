#include <tester.hpp>

void	test_map(void) {
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
	for (ft::map<char, std::string>::iterator it = rosalia.begin(), last = rosalia.end(); it != last ; it++)
		std::cout << (*it).first << " de " << (*it).second << std::endl;
	ft::map<char, std::string> abecedario;
	for (char c = 'a';c <= 'z';c++)
		abecedario[c] = std::string(((int)c % 3) + 1, c);
	for (ft::map<char, std::string>::iterator it = abecedario.begin(), last = abecedario.end(); it != last ; it++)
		std::cout << "['" << (*it).first << "']" << "=> \"" << (*it).second << '"' << std::endl;
	std::cout << std::endl;
	for (ft::map<char, std::string>::reverse_iterator rit = abecedario.rbegin(), last = abecedario.rend(); rit != last ; rit++)
		std::cout << "['" << (*rit).first << "']" << "=> \"" << (*rit).second << '"' << std::endl;
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
	std::cout << (rosalia.size() == rowsaleah.size()) << std::endl;
	rosalia.insert(ft::make_pair('0', "[ * t H 3 ~ ^ 0 i D * ]"));
	rowsaleah.swap(rosalia);
	std::cout << rosalia.size() << ' ';
	if (rosalia.find('0') != rosalia.end())
		std::cout << rosalia['0'] << std::endl;
	else
		std::cout << "Element not found" << std::endl;
	std::cout << rowsaleah.size() << " " << rowsaleah['0'] << std::endl;
}