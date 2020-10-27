/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:57:32 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/20 16:10:27 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

u_int32_t	func_f(u_int32_t abcd[4])
{
	return ((abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]));
}

u_int32_t	func_g(u_int32_t abcd[4])
{
	return ((abcd[1] & abcd[3]) | (abcd[2] & (~abcd[3])));
}

u_int32_t	func_h(u_int32_t abcd[4])
{
	return (abcd[1] ^ abcd[2] ^ abcd[3]);
}

u_int32_t	func_i(u_int32_t abcd[4])
{
	return (abcd[2] ^ (abcd[1] | ~abcd[3]));
}
