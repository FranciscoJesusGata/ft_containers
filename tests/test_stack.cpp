/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:10:06 by fgata-va          #+#    #+#             */
/*   Updated: 2023/01/16 21:55:12 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tester.hpp>

template <typename STK>
void	print_stack(STK &stk)
{
	for (size_t i = 0 ; i > stk.size() ; i++)
	{
		std::cout << "\t|" << stk.top() << std::endl;
		stk.pop();
	}
}

template <typename STK>
void	rel_oper_tests(const STK &a, const STK &b)
{
	std::cout << "\tEquals: " << (a == b) << std::endl;
	std::cout << "\tNot equals: " << (a != b) << std::endl;
	std::cout << "\tLess than: " << (a < b) << std::endl;
	std::cout << "\tLess or equals: " << (a <= b) << std::endl;
	std::cout << "\tGreater than: " << (a > b) << std::endl;
	std::cout << "\tGreater or equals: " << (a >= b) << std::endl;
	std::cout << std::endl;
}

void	test_stack(void) {
	std::cout << "Basic behaviour tests:" << std::endl;
	{
		ft::stack<int> tired;

		std::cout << std::boolalpha;
		std::cout << "\tempty(): " << tired.empty() << std::endl;
		tired.push(64);
		tired.push(42);
		tired.push(32);
		tired.push(21);
		tired.push(19);
		std::cout << "\tempty(): " << tired.empty() << std::endl;
		print_stack(tired);	
		std::cout << std::noboolalpha;
	}
	std::cout << "Copy constructor test:" << std::endl;
	{
		ft::stack<std::string> sleepy;

		sleepy.push("this is");
		sleepy.push("a certified");
		sleepy.push("hood");
		sleepy.push("classic");
		sleepy.push("dame da ne");
		sleepy.push("dame yo dame na no yo");
		sleepy.push("anta ga suki de sukisugite");
		sleepy.push("dore dake tsuyoi osake demo");
		sleepy.push("yugamanai omoide ga baka mitai");

		ft::stack<std::string> drained(sleepy);

		std::cout << "\t" << sleepy.size() << " | " << drained.size() << std::endl;
		print_stack(sleepy);

		drained.push("baka mitai hontou baka ne");
		drained.push("anta shinjiru bakari de");
		drained.push("tsuyoi onna no furi setsunasa no yokaze abiru");
		drained.push("hitori ni natte sannen ga sugi");
		drained.push("machinami sae mo kawarimashita");
		drained.push("na no ni na no ni doushite miren dake okizari");

		print_stack(drained);
	}
	std::cout << "Relational operators tests:" << std::endl;
	{
		ft::stack<int> damn_boi;

		for (int i = 1 ; i <= 5 ; i++)
			damn_boi.push(i * 5);
		ft::stack<int> epic_gamer(damn_boi);
		std::cout << std::boolalpha;
		rel_oper_tests(damn_boi, epic_gamer);
		std::cout << std::noboolalpha;
	}
}