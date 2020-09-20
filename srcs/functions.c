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

uint32_t	func_f(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | (~x & z));
}

uint32_t	func_g(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (y & (~z)));
}

uint32_t	func_h(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t	func_i(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | ~z));
}
