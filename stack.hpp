/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:17:32 by fgata-va          #+#    #+#             */
/*   Updated: 2022/06/06 11:54:46 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <vector.hpp>

namespace ft {
	template <class T, class Container = vector<T> >
	class stack {
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			explicit stack (const container_type& ctnr = container_type()): c(ctnr) {}

			bool				empty() const { return (c.empty()); }
			size_type			size() const { return (c.size()); }
			value_type&			top() { return (c.back()); }
			const value_type&	top() const { return (c.back()); }
			void				push(const value_type& val) { c.push_back(val); }
			void				pop() { c.pop_back(); }
			bool friend operator==(const stack& x,const stack& y) { return (x.c == y.c); }
			bool friend operator< (const stack& x,const stack& y) { return (x.c < y.c); }
			bool friend operator!=(const stack& x,const stack& y) { return (x.c != y.c); }
			bool friend operator> (const stack& x,const stack& y) { return (x.c > y.c); }
			bool friend operator>=(const stack& x,const stack& y) { return (x.c >= y.c); }
			bool friend operator<=(const stack& x,const stack& y) { return (x.c <= y.c); }
		protected:
			container_type	c;
	};
};

#endif
