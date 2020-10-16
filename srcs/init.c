/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:19:46 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/06 18:23:37 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

void	init_sha256(t_sha256 *vars)
{
	vars->h[0] = H1;
	vars->h[1] = H2;
	vars->h[2] = H3;
	vars->h[3] = H4;
	vars->h[4] = H5;
	vars->h[5] = H6;
	vars->h[6] = H7;
	vars->h[7] = H8;
}

void	init_md5(t_md5 *vars)
{
	init_tab(vars);
	init_s(vars);
	vars->abcd[0] = A;
	vars->abcd[1] = B;
	vars->abcd[2] = C;
	vars->abcd[3] = D;
}

void	init_tab(t_md5 *vars)
{
	int i;

	i = 0;
	while (i < 64)
	{
		vars->tab[i] = (unsigned long)(fabs(sin(i + 1)) * pow(2, 32));
		i++;
	}
}

void	init_s(t_md5 *vars)
{
	int i;

	i = -1;
	if (!(vars->s = malloc(4 * sizeof(vars->s))))
		return ;
	while (++i < 4)
		if (!(vars->s[i] = malloc(4 * sizeof(vars->s[i]))))
			return ;
	vars->s[0][0] = 7;
	vars->s[0][1] = 12;
	vars->s[0][2] = 17;
	vars->s[0][3] = 22;
	vars->s[1][0] = 5;
	vars->s[1][1] = 9;
	vars->s[1][2] = 14;
	vars->s[1][3] = 20;
	vars->s[2][0] = 4;
	vars->s[2][1] = 11;
	vars->s[2][2] = 16;
	vars->s[2][3] = 23;
	vars->s[3][0] = 6;
	vars->s[3][1] = 10;
	vars->s[3][2] = 15;
	vars->s[3][3] = 21;
}

void	init_all(t_all *all)
{
	all->flags = 0;
	all->av = NULL;
	all->listen_flag = 1;
	all->ac = 0;
	all->read_entry = 1;
}
