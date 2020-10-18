/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:19:22 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/17 18:09:11 by nsondag          ###   ########.fr       */
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

uint32_t	*padding(uint32_t *block, int64_t len, t_all *all)
{
	uint64_t	bit_len;
	uint64_t	bit_len2;
	int			i;

	i = 0;
	bit_len = ((uint64_t)len - 1) * 8;
	bit_len2 = bit_len >> 32;
	if (ft_strequ(all->command, "SHA256"))
	{
		bit_len = rev_int_byte(bit_len);
		bit_len2 = rev_int_byte(bit_len2);
		i = 1;
	}
	len = len % 64;
	ft_memcpy(block + 14 + i, &bit_len, 4);
	ft_memcpy(block + 15 - i, &bit_len2, 4);
	return (block);
}

void		get_blocks(t_all *all, uint32_t **block, int64_t *len)
{
	int64_t i;

	all->message[*len] = (unsigned char)128;
	all->message[*len + 1] = 0;
	all->nb_blocks = *len / 64 + 1;
	if (*len % 64 >= 56)
		all->nb_blocks++;
	if (!(block = malloc(all->nb_blocks * sizeof(*block))))
		return ;
	i = -1;
	*len += 1;
	if (ft_strequ(all->command, "MD5"))
		ft_md5(all, block, *len);
	else if (ft_strequ(all->command, "SHA256"))
		ft_sha256(all, block, *len);
	free(block);
}
