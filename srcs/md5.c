/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:22:51 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/27 16:19:59 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

static u_int32_t	g_s[4][4] = {
	{7, 12, 17, 22},
	{5, 9, 14, 20},
	{4, 11, 16, 23},
	{6, 10, 15, 21}
};

static u_int32_t	g_tab[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void			init_md5(u_int32_t *vars)
{
	vars[0] = 0x67452301;
	vars[1] = 0xefcdab89;
	vars[2] = 0x98badcfe;
	vars[3] = 0x10325476;
}

static u_int32_t	process_round(u_int32_t *vars, u_int32_t word[16], int i)
{
	int			index;
	u_int32_t	a;

	if (i < 16)
	{
		index = i % 16;
		a = vars[0] + func_f(vars) + word[index] + g_tab[i];
		return (vars[1] + left_rot(a, g_s[0][i % 4]));
	}
	else if (i < 32)
	{
		index = (5 * (i - 16) + 1) % 16;
		a = vars[0] + func_g(vars) + word[index] + g_tab[i];
		return (vars[1] + left_rot(a, g_s[1][i % 4]));
	}
	else if (i < 48)
	{
		index = (3 * (i - 32) + 5) % 16;
		a = vars[0] + func_h(vars) + word[index] + g_tab[i];
		return (vars[1] + left_rot(a, g_s[2][i % 4]));
	}
	index = (7 * (i - 48)) % 16;
	a = vars[0] + func_i(vars) + word[index] + g_tab[i];
	return (vars[1] + left_rot(a, g_s[3][i % 4]));
}

static u_int32_t	*process_block_md5(u_int32_t word[16], u_int32_t *vars)
{
	u_int32_t	tmp_vars[4];
	u_int32_t	tmp;
	int			i;

	ft_memcpy(tmp_vars, vars, 16);
	i = -1;
	while (++i < 64)
	{
		tmp = process_round(vars, word, i);
		vars[0] = vars[3];
		vars[3] = vars[2];
		vars[2] = vars[1];
		vars[1] = tmp;
	}
	i = -1;
	while (++i < 4)
		vars[i] = vars[i] + tmp_vars[i];
	return (vars);
	i = 0;
}

void				ft_md5(t_all *all, u_int32_t **block, int64_t len)
{
	int64_t		i;
	u_int32_t	*res;
	int			to_copy;

	i = -1;
	res = NULL;
	init_md5(all->vars);
	while (++i < all->nb_blocks)
	{
		if (!(block[i] = malloc(64 * sizeof(**block))))
			return ;
		ft_bzero(block[i], 64);
		to_copy = len < 64 ? len : 64;
		ft_memcpy(block[i], all->message + (i * 64), to_copy);
		if (i == all->nb_blocks - 1)
			block[i] = padding(block[i], len, all);
		res = process_block_md5(block[i], all->vars);
		free(block[i]);
	}
	i = -1;
	while (++i < 4)
	{
		res[i] = rev_int_byte(res[i]);
		ft_printf("%08x", res[i]);
	}
}
