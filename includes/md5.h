/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:23:05 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/20 18:36:30 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"

# define A 0x67452301
# define B 0xefcdab89
# define C 0x98badcfe
# define D 0x10325476

union	u_word
{
	unsigned char  tab[4];
	uint32_t         x;
}		word;

typedef struct s_md5
{
	int nb_blocks;
	unsigned long tab[64];
	int s1[4];
	int s2[4];
	int s3[4];
	int s4[4];
}	t_md5;

uint32_t left_rot(uint32_t a, int s);
uint32_t func_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t func_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t func_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t func_i(uint32_t x, uint32_t y, uint32_t z);
#endif
