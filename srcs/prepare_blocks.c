/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:19:22 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/07 19:33:48 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

/*
** Padding:
** Message must have a length multiple of 512 and contain the length
** of the original message
** First add a 1 bit after the message, then 0 until multiple of 512,
** except for the last 64 bits who will contain de original length of the
** message
*/

union u_word	*padding(union u_word *block, int len)
{
	union u_word	*word;
	uint64_t		bit_len;
	uint64_t		bit_len2;

	printf("%d\n", len);
	if (!(word = malloc(64 * sizeof(*word))))
		return (NULL);
	ft_bzero(word, 256);
	bit_len = rev_int_byte(((uint64_t)len - 1) * 8);
	bit_len2 = rev_int_byte(bit_len >> 32);
	len = len % 64;
	ft_memcpy(word, block, len);
	ft_memcpy(word + 15, &bit_len, 4);
	ft_memcpy(word + 14, &bit_len2, 4);
	return (word);
}

union u_word *prepare_sha256(union u_word *word)
{
	int i;

	i = -1;
	while (++i < 64)
		word[i].x = rev_int_byte(word[i].x);
	i = 16;
	while (i < 64)
	{
		word[i].x = sum4(word[i - 2].x) + word[i - 7].x + sum3(word[i - 15].x) + word[i - 16].x;
		i++;
	}
	i = 0;
	//while (i < 64)
	//	printf("%x\n", word[i++].x);
	return(word);
}

void			process_md5(t_all *all, union u_word	**block)
{
	int			i;
	uint32_t	*res;

	i = 0;
	all->md5_vars.abcd[0] = A;
	all->md5_vars.abcd[1] = B;
	all->md5_vars.abcd[2] = C;
	all->md5_vars.abcd[3] = D;
	while (i < all->nb_blocks)
		res = ft_md5(block[i++], &all->md5_vars);
	i = -1;
	while (++i < 4)
	{
		res[i] = rev_int_byte(res[i]);
		printf("%08x", res[i]);
	}
}

void			process_sha256(t_all *all, union u_word	**block)
{
	int			i;
	uint32_t	*res;

	if (!(res = malloc(256 * sizeof(*res))))
		return ;
	ft_bzero(res, 256);
	i = -1;
	while (++i < all->nb_blocks)
		block[i] = prepare_sha256(block[i]);
	i = 0;
	while (i < all->nb_blocks)
		res = ft_sha256(block[i++]);
	i = -1;
	while (++i < 8)
	{
		//res[i] = rev_int_byte(res[i]);
		printf("%08x", res[i]);
	}
}

void			get_blocks(t_all *all, union u_word	**block, int *len)
{
	int i;

	all->message[*len] = (unsigned char)128;
	all->message[*len + 1] = 0;
	all->nb_blocks = *len / 64 + 1;
	if (*len % 64 >= 56)
		all->nb_blocks++;
	if (!(block = malloc(all->nb_blocks * sizeof(*block))))
		return ;
	i = -1;
	while (++i < all->nb_blocks)
	{
		if (!(block[i] = malloc(64 * sizeof(**block))))
			return ;
	}
	i = -1;
	*len += 1;
	while ((++i * 64) < *len)
		ft_memcpy(block[i], all->message + (i * 64), 64);
	if (i == all->nb_blocks)
		i--;
	block[i] = padding(block[i], *len);
	//process_md5(all, block);
	process_sha256(all, block);
}
