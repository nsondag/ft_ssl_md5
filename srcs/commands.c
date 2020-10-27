/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:20:11 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/07 19:31:36 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

static char	*g_md_commands[3] = {"MD5", "SHA256", "\0"};
static char	*g_cipher_commands[1] = {"\0"};
static char	*g_standard_commands[1] = {"\0"};

int		show_commands(void)
{
	int i;

	ft_printf("\nStandard commands:\n");
	i = 0;
	while (*g_standard_commands[i])
		ft_printf("%s\n", g_standard_commands[i++]);
	ft_printf("\nMessage Digest commands:\n");
	i = 0;
	while (*g_md_commands[i])
		ft_printf("%s\n", g_md_commands[i++]);
	ft_printf("\nCipher commands:\n");
	i = 0;
	while (*g_cipher_commands[i])
		ft_printf("%s\n", g_cipher_commands[i++]);
	return (0);
}

int		is_command(char *command)
{
	int i;

	ft_strtoupper(command, command);
	i = -1;
	while (*g_md_commands[++i])
	{
		if (ft_strequ(command, g_md_commands[i]))
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
					return (1);
				ft_memcpy(all->av, &av[i], ft_strlen(av) - i);
				return (0);
			}
		}
		else
		{
			ft_printf("%s: illegal option -- %c\n", all->command, av[i]);
			return (1);
		}
	}
	return (0);
}
