/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:48:33 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/28 17:39:11 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

/* Padding:
   Message must have a length multiple of 512 and contain the length
   of the original message
   First add a 1 bit after the message, then 0 until multiple of 512,
   except for the last 64 bits who will contain de original length of the
   message
   */

uint32_t			rev_int_byte(uint32_t nbr)
{
	return ((nbr & 0xff) << 24 | (nbr & 0xff0000) >> 8 |
			(nbr & 0xff00) << 8 | (nbr & 0xff000000) >> 24);
}

union u_word *padding(union u_word *block, int len, int check)
{
	union u_word *word;
	int bit_len;

	if (!(word = malloc(16 * sizeof(*word))))
		return (NULL);
	ft_bzero(word, 64);
	bit_len = len * 8;
	len = len % 64;
	//printf("len %d\n", len);
	//printf("%u\n", block->x);
	ft_memcpy(word, block, len);
	//printf("test\n");
	if (check)
	{
		//printf("do 1\n");
		word[len / 4].tab[len % 4] = 128;
	}
	if (check % 2 == 0)
	{
		//printf("do 2\n");
		ft_memcpy(word + 14, &bit_len, 4);
	}
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

void init_tab(t_md5 *vars)
{
	int i = 0;

	while (i < 64)
	{
		vars->tab[i] = (unsigned long)(fabs(sin(i + 1)) * pow(2, 32));
		i++;
	}
}

void init_s(t_md5 *vars)
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

uint32_t ft_md5(union u_word word[16], t_md5 *vars)
{
	static uint32_t abcd[4] = {A, B, C, D};
	uint32_t result[4] = {0, 0, 0, 0};
	uint32_t tmp_abcd[4] = {A, B, C, D};
	uint32_t tmp;
	int i;

	ft_memcpy(tmp_abcd, abcd, 16);
	i = 0;
	while (i < 16)
	{
		//printf("word: %u", word[i].x);
		//printf(" %c", word[i].tab[0]);
		//printf(" %c", word[i].tab[1]);
		//printf(" %c", word[i].tab[2]);
		//printf(" %c\n", word[i].tab[3]);
		i++;
	}
	i = 0;
	while (i < 64)
	{
		if (i < 16)
			tmp = r1(abcd, word, vars->s[0][i % 4], i, vars->tab);
		else if (i < 32)
			tmp = r2(abcd, word, vars->s[1][i % 4], i, vars->tab);
		else if (i < 48)
			tmp = r3(abcd, word, vars->s[2][i % 4], i, vars->tab);
		else
			tmp = r4(abcd, word, vars->s[3][i % 4], i, vars->tab);
		//printf("abcd: %u\n", tmp);
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
	//printf("%x%x%x%x\n", result[0], result[1], result[2], result[3]);
	return (0);
}

int process (int argc, char **argv, int flags)
{
	t_md5 vars;
	union u_word *result;
	union u_word **block;
	int i;
	int j;
	int len;
	char *string;
	int	check;

	check = 0;
	string = NULL;
	if (argc < 2)
		parser(string, argv[1], &vars);
	else
		vars.message = argv[1];
	init_s(&vars);
	init_tab(&vars);
	vars.nb_blocks = ft_strlen(vars.message) / 56 + 1; // wrong !!!!???
	//printf("len_message %zu\n", ft_strlen(vars.message));
	//printf("nb_blocks %d\n", vars.nb_blocks);
	if (!(block = malloc(vars.nb_blocks * sizeof(*block))))
		return (0);
	j = 0;
	while (j < vars.nb_blocks)
	{
		if (!(block[j++] = malloc(64 * sizeof(**block))))
			return (0);
	}
	i = 0;
	j = 0;
	len = ft_strlen(vars.message);
	while (i < len - 8)
	{
		ft_memcpy(block[j], vars.message + i, 64);
		i += 64;
		//printf("i %d\n", i);
		if (i % 64 == 0)
		{
			//printf("teest\n");
			if (i != 64)
		 		block[j] = padding(block[j], len, 1);
			else
				check = 2;
		//	printf("check %d\n", check);
		}
		j += 1;
	}
	ft_memcpy(block[j], vars.message + i, len / 64);
	//printf("j %d\n", j);
	block[j] = padding(block[j], len, check);
	//printf("after padding\n");
	j = 0;
	while (j < vars.nb_blocks)
		ft_md5(block[j++], &vars);
	return (0);
}

int dispatch(int argc, char **argv, char *command, int flags)
{
	if (ft_strequ(command, "md5"))
	{
		printf("WIP!!!\n");
		process(argc, argv, flags);
	}
	else if (ft_strequ(command, "sha256"))
		printf("COMMING SOON!!!\n");
	return (0);
}

int main(int argc, char **argv)
{
	int i;
	int flags;

	if (argc < 2)
	{
		printf("usage: ft_ssl command [command opts] [command args]\n");
		return (1);
	}
	else if (!is_command(argv[1]))
	{
		printf("ft_ssl: Error '%s' is an invalid command.\n", argv[1]);
		show_commands();
		return (1);
	}
	i = 2;
	while (i < argc)
	{
		if (*argv[i] == '-')
			is_valid_flag(argv[1], &argv[i][1], &flags);
		i++;
	}
	dispatch(argc, argv, argv[1], flags);
	return (0);
}
