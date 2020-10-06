/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:57:32 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/20 16:10:27 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

uint32_t	left_rot(uint32_t a, int s)
{
	unsigned	mask;

	mask = (1 << s) - 1;
	return ((a >> (32 - s)) & mask) | ((a << s) & ~mask);
}

uint32_t	func_f(uint32_t abcd[4])
{
	return ((abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]));
}

uint32_t	func_g(uint32_t abcd[4])
{
	return ((abcd[1] & abcd[3]) | (abcd[2] & (~abcd[3])));
}

uint32_t	func_h(uint32_t abcd[4])
{
	return (abcd[1] ^ abcd[2] ^ abcd[3]);
}

uint32_t	func_i(uint32_t abcd[4])
{
	return (abcd[2] ^ (abcd[1] | ~abcd[3]));
}
