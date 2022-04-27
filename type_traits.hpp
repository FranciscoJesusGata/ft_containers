/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:20:53 by fgata-va          #+#    #+#             */
/*   Updated: 2022/04/27 17:23:53 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft {
	/*************
	 * enable_if *
	 *************/

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	/***************
	 * is_integral *
	 ***************/

	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator T() const { return v; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template <class T> struct is_integral: false_type {};
	template <> struct is_integral<bool>: true_type {};
	template <> struct is_integral<char>: true_type {};
	//template <> struct is_integral<char16_t>: true_type {};
	//template <> struct is_integral<char32_t>: true_type {};
	template <> struct is_integral<wchar_t>: true_type {};
	template <> struct is_integral<signed char>: true_type {};
	template <> struct is_integral<short int>: true_type {};
	template <> struct is_integral<int>: true_type {};
	template <> struct is_integral<long int>: true_type {};
	template <> struct is_integral<long long int>: true_type {};
	template <> struct is_integral<unsigned char>: true_type {};
	template <> struct is_integral<unsigned short int>: true_type {};
	template <> struct is_integral<unsigned int>: true_type {};
	template <> struct is_integral<unsigned long int>: true_type {};
	template <> struct is_integral<unsigned long long int>: true_type {};
}

#endif
