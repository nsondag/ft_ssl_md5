/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:48:33 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/06 18:32:46 by nsondag          ###   ########.fr       */
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

uint32_t		rev_int_byte(uint32_t nbr)
{
	return ((nbr & 0xff) << 24 | (nbr & 0xff0000) >> 8 |
			(nbr & 0xff00) << 8 | (nbr & 0xff000000) >> 24);
}

union u_word	*padding(union u_word *block, int len)
{
	union u_word	*word;
	uint64_t				bit_len;
	uint64_t				bit_len2;

	if (!(word = malloc(16 * sizeof(*word))))
		return (NULL);
	ft_bzero(word, 64);
	bit_len = ((uint64_t)len - 1) * 8;
	bit_len2 = bit_len >> 32;
	len = len % 64;
	ft_memcpy(word, block, len);
	ft_memcpy(word + 14, &bit_len, 4);
	ft_memcpy(word + 15, &bit_len2, 4);
	return (word);
}

void get_blocks(t_all *all, union u_word	**block, int *len)
{

		int j = 0;
		int i = 0;

		*len = ft_strlen(all->message);
		all->message[*len] = (unsigned char)128;
		all->message[*len + 1] = 0;
		all->nb_blocks = *len / 64 + 1;
		if (*len % 64 >= 56)
			all->nb_blocks++;
		if (!(block = malloc(all->nb_blocks * sizeof(*block))))
			return ;
		j = 0;
		while (j < all->nb_blocks)
		{
			if (!(block[j++] = malloc(64 * sizeof(**block))))
				return ;
		}
		i = 0;
		j = 0;
		*len += 1;
		while (i < *len)
		{
			ft_memcpy(block[j], all->message + i, 64);
			i += 64;
			j++;
		}
		if (j == all->nb_blocks)
			j--;
		block[j] = padding(block[j], *len);
		process_md5_blocks(all, block);
}

void process_md5(t_all *all, union u_word	**block)
{
	int i;
	uint32_t *res;

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

int				process(char *av, t_all *all)
{
	union u_word	*result;
	union u_word	**block;
	int				i;
	int				j;
	int				len;   // length of the message
	char			*string; //

	string = NULL;
	len = 0;
	if (all->flags & S && all->listen_flag)
	{
		all->flags &= ~S;
		all->message = av;
		if (!(all->flags & Q) && !(all->flags & R))
			printf("%s (\"%s\") = ", all->command, all->message);
	}
	else
	{
		if ((len = parser(all->message, av, all)) < 0)
			return (0);
		if (all->flags & P)
		{
			all->read_entry = 0;
			if (all->read_entry)
				printf("\n");
			all->flags &= ~P;
		}
	}
	if (!len)
		len = ft_strlen(all->message);
	all->message[len] = (unsigned char)128;
	all->message[len + 1] = 0;
	all->nb_blocks = len / 64 + 1;
	if (len % 64 >= 56)
		all->nb_blocks++;
	if (!(block = malloc(all->nb_blocks * sizeof(*block))))
		return (0);
	j = 0;
	while (j < all->nb_blocks)
	{
		if (!(block[j++] = malloc(64 * sizeof(**block))))
			return (0);
	}
	i = 0;
	j = 0;
	len++;
	while (i < len)
	{
		ft_memcpy(block[j], all->message + i, 64);
		i += 64;
		j++;
	}
	if (j == all->nb_blocks)
		j--;
	block[j] = padding(block[j], len);
	process_md5(all, block);
	all->message[len - 1] = 0;
	if ((all->flags & R) && !(all->flags & Q) && *all->message)
			printf(" \"%s\"\n", all->message);
	else
		printf("\n");
	return (0);
}

int				dispatch(t_all *all)
{
	if (ft_strequ(all->command, "md5"))
		process(all->av, all);
	else if (ft_strequ(all->command, "sha256"))
		printf("COMMING SOON!!!\n");
	free(all->av);
	all->av = NULL;
	return (0);
}

int			check_validity(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("usage: ft_ssl command [command opts] [command args]\n");
		return (0);
	}
	else if (!is_command(argv[1]))
	{
		printf("ft_ssl: Error '%s' is an invalid command.\n", argv[1]);
		show_commands();
		return (0);
	}
	else
		return (1);
}

int			main(int argc, char **argv)
{
	int		i;
	t_all	all;

	if (!check_validity(argc, argv))
		return (1);
	init_all(&all);
	ft_memcpy(all.command, argv[1], ft_strlen(argv[1]));
	if (ft_strequ(all.command, "md5") == 1)
		init_md5(&all.md5_vars);
	else if (ft_strequ(all.command, "sha256") == 1)
		init_sha256(&all.sha256_vars);
	i = 2;
	while (i < argc)
	{
		if (all.av || (all.flags & P))
			dispatch(&all);
		else if (*argv[i] == '-' && !(all.flags & S) && all.listen_flag)
			is_valid_flag(&all, &argv[i++][1]);
		else
		{
			if (!(all.av = malloc((ft_strlen(argv[i]) + 1) * sizeof(all.av))))
				return (1);
			ft_strcpy(all.av, argv[i++]);
			all.ac++;
			dispatch(&all);
		}
	}
	if (all.flags & S && !all.ac)
		printf("%s: option requires an argument -- s\n", all.command);
	else if (!all.ac || all.flags & P || all.flags & S)
		dispatch(&all);
	return (0);
}
