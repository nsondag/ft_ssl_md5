/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:20:11 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/28 14:45:38 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

static char	*g_md_cmds[3] = {"MD5", "SHA256", "\0"};
static char	*g_cipher_cmds[1] = {"\0"};
static char	*g_standard_cmds[1] = {"\0"};

int		show_cmds(void)
{
	int i;

	ft_printf("\nStandard cmds:\n");
	i = 0;
	while (*g_standard_cmds[i])
		ft_printf("%s\n", g_standard_cmds[i++]);
	ft_printf("\nMessage Digest cmds:\n");
	i = 0;
	while (*g_md_cmds[i])
		ft_printf("%s\n", g_md_cmds[i++]);
	ft_printf("\nCipher cmds:\n");
	i = 0;
	while (*g_cipher_cmds[i])
		ft_printf("%s\n", g_cipher_cmds[i++]);
	return (0);
}

int		is_cmd(t_all *all)
{
	int i;

	if (ft_strlen(all->cmd) > 32)
		return (0);
	ft_strtoupper(all->uppercmd, all->cmd);
	i = -1;
	while (*g_md_cmds[++i])
	{
		if (ft_strequ(all->uppercmd, g_md_cmds[i]))
			return (1);
	}
	return (0);
}

int		is_valid_flag(t_all *all, char *av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (ft_strchr(FLAG, av[i]))
		{
			all->flags |= (int)ft_pow(2, av[i++] - 'p');
			if (all->flags & S && av[i])
			{
				all->ac++;
				if (!(all->av = malloc((ft_strlen(av) - i) * sizeof(*all->av))))
					return (-1);
				ft_memcpy(all->av, &av[i], ft_strlen(av) - i);
				return (1);
			}
		}
		else
		{
			ft_printf("%s: illegal option -- %c\nusage: ", all->cmd, av[i]);
			ft_printf("ft_ssl %s [-pqr] [-s string] [files ...]\n", all->cmd);
			return (-1);
		}
	}
	return (1);
}
