/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:48:33 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/07 19:31:15 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

uint32_t		rev_int_byte(uint32_t nbr)
{
	return ((nbr & 0xff) << 24 | (nbr & 0xff0000) >> 8 |
			(nbr & 0xff00) << 8 | (nbr & 0xff000000) >> 24);
}

int				process(char *av, t_all *all)
{
	union u_word	*result;
	union u_word	**block;
	int				len;
	char			*string;

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
	get_blocks(all, block, &len);
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

int				check_validity(int argc, char **argv)
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

int				main(int argc, char **argv)
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
