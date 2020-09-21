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

union u_word *padding(char *message)
{
	union u_word *word;
	int len;

	if (!(word = malloc(16 * sizeof(*word))))
		return (NULL);
	ft_bzero(word, 64);
	len = ft_strlen(message) * 8;
	ft_memcpy(word, message, len / 8);
	word[len / 32].tab[(len / 8) % 4] = 128;
	ft_memcpy(word + 14, &len, 4);
	return (word);
}

uint32_t r1(uint32_t abcd[4], union u_word word[16], int s, int i, unsigned long tab[64])
{
	abcd[0] = (abcd[1] + left_rot((abcd[0] + func_f(abcd[1], abcd[2], abcd[3]) + word[i % 16].x + tab[i]), s));
	return (abcd[0]);
}

uint32_t r2(uint32_t abcd[4], union u_word word[16], int s, int i, unsigned long tab[64])
{
	abcd[0] = (abcd[1] + left_rot((abcd[0] + func_g(abcd[1], abcd[2], abcd[3]) + word[(5 * (i - 16) + 1) % 16].x + tab[i]), s));
	return (abcd[0]);
}

uint32_t r3(uint32_t abcd[4], union u_word word[16], int s, int i, unsigned long tab[64])
{
	abcd[0] = (abcd[1] + left_rot((abcd[0] + func_h(abcd[1], abcd[2], abcd[3]) + word[(3 * (i - 32) + 5) % 16].x + tab[i]), s));
	return (abcd[0]);
}

uint32_t r4(uint32_t abcd[4], union u_word word[16], int s, int i, unsigned long tab[64])
{
	abcd[0] = (abcd[1] + left_rot((abcd[0] + func_i(abcd[1], abcd[2], abcd[3]) + word[(7 * (i - 48)) % 16].x + tab[i]), s));
	return (abcd[0]);
}

uint32_t ft_md5(union u_word word[16])
{
	uint32_t abcd[4] = {A, B, C, D};
	int i = 0;
	uint32_t tmp_abcd[4] = {A, B, C, D};
	int s1[4] = {7, 12, 17, 22};
	int s2[4] = {5, 9, 14, 20};
	int s3[4] = {4, 11, 16, 23};
	int s4[4] = {6, 10, 15, 21};
	uint32_t tmp = 0;
	unsigned long tab[64];
	while (i < 64)
	{
		tab[i] = (unsigned long)(fabs(sin(i + 1)) * pow(2, 32));
		i++;
	}
	i = 0;
	while (i < 64)
	{
		printf("%u %u %u %u\n", abcd[0], abcd[1], abcd[2], abcd[3]);
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
		abcd[i] = rev_int_byte(abcd[i] + tmp_abcd[i]);
		i++;
	}
	printf("%x%x%x%x\n", abcd[0], abcd[1], abcd[2], abcd[3]);
	return (0);
}

int main(int argc, char **argv)
{
	union u_word *result;

	if (argc < 2)
	{
		write(2, "usage\n", 6);
		return (0);
	}
	else
	{
		//printf("%s\n", argv[1]);
		result = padding(argv[1]);
		//printf("%s\n", argv[1]);
		ft_md5(result);
		//printf("%s\n", result);
	}
	return (0);
}
