/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:23:39 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/16 16:04:32 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

u_int32_t	ch(u_int32_t x, u_int32_t y, u_int32_t z)
{
	return ((x & y) ^ (~x & z));
}

u_int32_t	maj(u_int32_t x, u_int32_t y, u_int32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

u_int32_t	sigma(u_int32_t x, int i)
{
	if (i == 1)
		return (right_rot(x, 2) ^ right_rot(x, 13) ^ right_rot(x, 22));
	else if (i == 2)
		return (right_rot(x, 6) ^ right_rot(x, 11) ^ right_rot(x, 25));
	else if (i == 3)
		return (right_rot(x, 7) ^ right_rot(x, 18) ^ left_shift(x, 3));
	else
		return (right_rot(x, 17) ^ right_rot(x, 19) ^ left_shift(x, 10));
}
