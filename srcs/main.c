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
	all->flags = 0;
	all->av = NULL;
	all->listen_flag = 1;
	all->ac = 0;
	all->read_entry = 1;
}

static int64_t	get_message(t_all *all)
{
	int64_t	len;

	if (all->flags & S && all->listen_flag)
	{
		all->message = ft_strdup(all->av);
		if (!(all->flags & Q) && !(all->flags & R))
			ft_printf("%s(\"%s\")= ", all->command, all->message);
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
		if (all->read_entry)
			ft_printf("\n");
		all->flags &= ~P;
	}
	if (!len)
		len = ft_strlen(all->message);
	return (len);
}

static int		process(t_all *all)
{
	u_int32_t	*result;
	u_int32_t	**block;
	int64_t		len;
	char		*string;

	string = NULL;
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
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		return (0);
	}
	else if (!is_command(argv))
	{
		ft_printf("ft_ssl: Error '%s' is an invalid command.\n", argv);
		show_commands();
		return (0);
	}
	else
	{
		init_all(all);
		ft_strcpy(all->command, argv);
		return (1);
	}
}

int				main(int argc, char **argv)
{
	int		i;
	t_all	all;

	if (!check_validity(argc, argv[1], &all))
		return (1);
	i = 2;
	while (i < argc)
	{
		if (all.av || (all.flags & P))
			process(&all);
		else if (*argv[i] == '-' && !(all.flags & S) && all.listen_flag)
			is_valid_flag(&all, &argv[i++][1]);
		else if (all.ac++)
		{
			if (!(all.av = malloc((ft_strlen(argv[i]) + 1) * sizeof(all.av))))
				return (1);
			ft_strcpy(all.av, argv[i++]);
			process(&all);
		}
	}
	if (all.flags & S && !all.ac)
		ft_printf("%s: option requires an argument -- s\n", all.command);
	else if (!all.ac || all.flags & P || all.flags & S)
		process(&all);
	return (0);
}
