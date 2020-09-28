/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:48:33 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/21 21:17:54 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

/* Padding:
   Message must have a length multiple of 512 and contain the length
   of the original message
   First add a 1 bit after the message, then 0 until multiple of 512,
   except for the last 64 bits who will contain de original length of the message
   */

uint32_t			rev_int_byte(uint32_t nbr)
{
	return ((nbr & 0xff) << 24 | (nbr & 0xff0000) >> 8 |
			(nbr & 0xff00) << 8 | (nbr & 0xff000000) >> 24);
}

union u_word *padding(union u_word *block, int len)
{
	union u_word *word;
	int bit_len;

	if (!(word = malloc(16 * sizeof(*word))))
		return (NULL);
	ft_bzero(word, 64);
	bit_len = len * 8;
	len = len % 64;
	ft_memcpy(word, block, len);
	word[len / 4].tab[len % 4] = 128;
	ft_memcpy(word + 14, &bit_len, 4);
	return (word);
}

uint32_t r1(uint32_t abcd[4], union u_word word[16], int s, int i, unsigned long tab[64])
{
	int index;

	index = i % 16;
	abcd[0] = abcd[1] + left_rot((abcd[0] + func_f(abcd[1], abcd[2], abcd[3]) + word[index].x + tab[i]), s);
	return (abcd[0]);
}

uint32_t r2(uint32_t abcd[4], union u_word word[16], int s, int i, unsigned long tab[64])
{
	int index;

	index = (5 * (i - 16) + 1) % 16;
	abcd[0] = abcd[1] + left_rot((abcd[0] + func_g(abcd[1], abcd[2], abcd[3]) + word[index].x + tab[i]), s);
	return (abcd[0]);
}

uint32_t r3(uint32_t abcd[4], union u_word word[16], int s, int i, unsigned long tab[64])
{
	int index;

	index = (3 * (i - 32) + 5) % 16;
	abcd[0] = abcd[1] + left_rot((abcd[0] + func_h(abcd[1], abcd[2], abcd[3]) + word[index].x + tab[i]), s);
	return (abcd[0]);
}

uint32_t r4(uint32_t abcd[4], union u_word word[16], int s, int i, unsigned long tab[64])
{
	int index;

	index = (7 * (i - 48)) % 16;
	abcd[0] = abcd[1] + left_rot((abcd[0] + func_i(abcd[1], abcd[2], abcd[3]) + word[index ].x + tab[i]), s);
	return (abcd[0]);
}

uint32_t ft_md5(union u_word word[16])
{

	static uint32_t abcd[4] = {A, B, C, D};
	uint32_t result[4] = {0, 0, 0, 0};
	int i = 0;
	uint32_t tmp_abcd[4] = {A, B, C, D};
	int s1[4] = {7, 12, 17, 22};
	int s2[4] = {5, 9, 14, 20};
	int s3[4] = {4, 11, 16, 23};
	int s4[4] = {6, 10, 15, 21};
	uint32_t tmp = 0;
	unsigned long tab[64];

	tmp_abcd[0] = abcd[0];
	tmp_abcd[1] = abcd[1];
	tmp_abcd[2] = abcd[2];
	tmp_abcd[3] = abcd[3];
	while (i < 64)
	{
		tab[i] = (unsigned long)(fabs(sin(i + 1)) * pow(2, 32));
		i++;
	}
	i = 0;
	while (i < 64)
	{
		if (i < 16)
			tmp = r1(abcd, word, s1[i % 4], i, tab);
		else if (i < 32)
			tmp = r2(abcd, word, s2[i % 4], i, tab);
		else if (i < 48)
			tmp = r3(abcd, word, s3[i % 4], i, tab);
		else
			tmp = r4(abcd, word, s4[i % 4], i, tab);
		abcd[0] = abcd[3];
		abcd[3] = abcd[2];
		abcd[2] = abcd[1];
		abcd[1] = tmp;
		i++;
	}
	i = 0;
	while(i < 4)
	{
		abcd[i] = abcd[i] + tmp_abcd[i];
		i++;
	}
	i = 0;
	while(i < 4)
	{
		result[i] = rev_int_byte(abcd[i]);
		i++;
	}
	printf("%x%x%x%x\n", result[0], result[1], result[2], result[3]);
	return (0);
}

int main(int argc, char **argv)
{
	union u_word *result;
	union u_word **block;
	int i;
	int j;
	int len;
	int nb_blocks;


	if (argc < 2)
	{
		write(2, "usage\n", 6);
		return (0);
	}
	else
	{
		nb_blocks = ft_strlen(argv[1]) / 64 + 1;
		if (!(block = malloc(nb_blocks * sizeof(*block))))
			return (0);
		j = 0;
		while (j < nb_blocks)
		{
			if (!(block[j++] = malloc(64 * sizeof(**block))))
				return (0);
		}
		j = 0;
		i = 0;
		len = ft_strlen(argv[1]);
		while (i < len - 64)
		{
			ft_memcpy(block[j], argv[1] + i, 64);
			i += 64;
			j += 1;
		}
		ft_memcpy(block[j], argv[1] + i, len % 64);
		block[j] = padding(block[j], len);
		j = 0;
		while (j < nb_blocks)
			ft_md5(block[j++]);
	}
	return (0);
}
