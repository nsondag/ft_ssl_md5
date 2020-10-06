/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:22:51 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/06 18:07:38 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

uint32_t	r1(t_md5 *vars, union u_word word[16], int i)
{
	int			index;
	uint32_t	r;
	uint32_t	a;

	index = i % 16;
	a = vars->abcd[0] + func_f(vars->abcd) + word[index].x + vars->tab[i];
	r = vars->abcd[1] + left_rot(a, vars->s[0][i % 4]);
	return (r);
}

uint32_t	r2(t_md5 *vars, union u_word word[16], int i)
{
	int			index;
	uint32_t	r;
	uint32_t	a;

	index = (5 * (i - 16) + 1) % 16;
	a = vars->abcd[0] + func_g(vars->abcd) + word[index].x + vars->tab[i];
	r = vars->abcd[1] + left_rot(a, vars->s[1][i % 4]);
	return (r);
}

uint32_t	r3(t_md5 *vars, union u_word word[16], int i)
{
	int			index;
	uint32_t	r;
	uint32_t	a;

	index = (3 * (i - 32) + 5) % 16;
	a = vars->abcd[0] + func_h(vars->abcd) + word[index].x + vars->tab[i];
	r = vars->abcd[1] + left_rot(a, vars->s[2][i % 4]);
	return (r);
}

uint32_t	r4(t_md5 *vars, union u_word word[16], int i)
{
	int			index;
	uint32_t	r;
	uint32_t	a;

	index = (7 * (i - 48)) % 16;
	a = vars->abcd[0] + func_i(vars->abcd) + word[index].x + vars->tab[i];
	r = vars->abcd[1] + left_rot(a, vars->s[3][i % 4]);
	return (r);
}

uint32_t	*ft_md5(union u_word word[16], t_md5 *vars)
{
	uint32_t	tmp_abcd[4];
	uint32_t	tmp;
	int			i;

	ft_memcpy(tmp_abcd, vars->abcd, 16);
	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			tmp = r1(vars, word, i);
		else if (i < 32)
			tmp = r2(vars, word, i);
		else if (i < 48)
			tmp = r3(vars, word, i);
		else
			tmp = r4(vars, word, i);
		vars->abcd[0] = vars->abcd[3];
		vars->abcd[3] = vars->abcd[2];
		vars->abcd[2] = vars->abcd[1];
		vars->abcd[1] = tmp;
	}
	i = -1;
	while (++i < 4)
		vars->abcd[i] = vars->abcd[i] + tmp_abcd[i];
	return (vars->abcd);
}
