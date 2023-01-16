/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:10:06 by fgata-va          #+#    #+#             */
/*   Updated: 2023/01/12 20:36:31 by fgata-va         ###   ########.fr       */
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
}
