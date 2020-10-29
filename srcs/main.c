/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:48:33 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/27 16:58:12 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

static void		init_all(t_all *all)
{
	all->fd = 0;
	all->flags = 0;
	all->av = NULL;
	all->listen_flag = 1;
	all->ac = 0;
	all->read_entry = 1;
}

static int64_t	get_message(t_all *all)
{
	int64_t	len;

	len = 0;
	if (all->flags & S && all->listen_flag)
	{
		if (!(all->message = ft_strdup(all->av)))
			return (-1);
		if (!(all->flags & Q) && !(all->flags & R))
			ft_printf("%s(\"%s\")= ", all->cmd, all->message);
	}
	else if ((len = parse(all->message, all->av, all)) < 0)
	{
		free(all->av);
		all->av = NULL;
		return (-1);
	}
	else if (all->flags & P)
	{
		all->read_entry = 0;
		all->read_entry ? ft_printf("\n") : 0;
		all->flags &= ~P;
	}
	if (!len)
		len = ft_strlen(all->message);
	return (len);
}

static int		process(t_all *all)
{
	u_int32_t	**block;
	int64_t		len;

	block = NULL;
	if ((len = get_message(all)) < 0)
		return (0);
	get_blocks(all, block, &len);
	all->message[len - 1] = 0;
	free(all->message);
	if ((all->flags & R) && !(all->flags & Q) && all->av)
	{
		if (all->flags & S)
			ft_printf(" \"%s\"\n", all->av);
		else
			ft_printf(" %s\n", all->av);
	}
	else
		ft_printf("\n");
	if (all->flags & S)
		all->flags &= ~S;
	free(all->av);
	all->av = NULL;
	return (0);
}

static int		check_validity(int argc, char *argv, t_all *all)
{
	if (argc < 2)
	{
		ft_printf("usage: ft_ssl command [-pqr] [-s string] [files ...]\n");
		return (0);
	}
	if (!is_cmd(all, argv))
	{
		ft_printf("ft_ssl: Error '%s' is an invalid command.\n", argv);
		show_cmds();
		return (0);
	}
	init_all(all);
	return (1);
}

int				main(int argc, char **argv)
{
	int		i;
	t_all	all;

	if (!check_validity(argc, argv[1], &all))
		return (1);
	i = 2;
	while (i > 0 && i < argc)
	{
		if (all.av || (all.flags & P))
			process(&all);
		else if (*argv[i] == '-' && !(all.flags & S) && all.listen_flag)
			i = is_valid_flag(&all, &argv[i++][1]) >= 0 ? i : -1;
		else if (all.ac++)
		{
			if (!(all.av = malloc((ft_strlen(argv[i]) + 1) * sizeof(all.av))))
				return (1);
			ft_strcpy(all.av, argv[i++]);
			process(&all);
		}
	}
	if (i > 0 && (all.flags & S && !all.ac))
		ft_printf("%s: option requires an argument -- s\n", all.cmd);
	else if (i > 0 && (!all.ac || all.flags & S || all.flags & P))
		process(&all);
	return (0);
}
