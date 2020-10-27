/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shifts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:10:19 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/16 16:13:52 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

u_int32_t	right_rot(u_int32_t a, int s)
{
	return (a << (32 - s) | (a >> s));
}

u_int32_t	left_rot(u_int32_t a, int s)
{
	return (a >> (32 - s) | (a << s));
}

u_int32_t	left_shift(u_int32_t a, int s)
{
	return (a >> s);
}

u_int32_t	rev_int_byte(u_int32_t nbr)
{
	return ((nbr & 0xff) << 24 | (nbr & 0xff0000) >> 8 |
			(nbr & 0xff00) << 8 | (nbr & 0xff000000) >> 24);
}
