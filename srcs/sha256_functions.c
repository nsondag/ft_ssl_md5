/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:23:39 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/14 14:23:41 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

uint32_t	right_rot(uint32_t a, int s)
{
	unsigned int mask;

	mask = (1 << s) - 1;
	//return((a << s) || a << ((32 - s)));
	return ((a << (32 - s)) & mask) | ((a >> s) & ~mask);
}

uint32_t	left_shift(uint32_t a, int s)
{
	return (a >> s);
}


uint32_t ch(uint32_t x, uint32_t y, uint32_t z)
{
  return ((x & y) ^ (~x & z));
}

uint32_t maj(uint32_t x, uint32_t y, uint32_t z)
{
  return((x & y) ^ (x & z) ^ (y & z));
}

uint32_t sum1(uint32_t x)
{
  return (right_rot(x, 2) ^ right_rot(x, 13) ^ right_rot(x, 22));
}

uint32_t sum2(uint32_t x)
{
  return (right_rot(x, 6) ^ right_rot(x, 11) ^ right_rot(x, 25));
}

uint32_t sum3(uint32_t x)
{
	printf("((%x))\n", x);
	printf("@ %x @ %x @ %x\n", right_rot(x,7), right_rot(x, 18), left_shift(x, 3));
  return (right_rot(x, 7) ^ right_rot(x, 18) ^ left_shift(x, 3));
}

uint32_t sum4(uint32_t x)
{
  return (right_rot(x, 17) ^ right_rot(x, 19) ^ left_shift(x, 10));
}
