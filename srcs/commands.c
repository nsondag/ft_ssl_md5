/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:20:11 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/29 17:44:36 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO replace printfs!!!!

#include "../includes/md5.h"

char	*g_md_commands[3] = {"md5", "sha256", "\0"};
char	*g_cipher_commands[1] = {"\0"};
char	*g_standard_commands[1] = {"\0"};

int		show_commands(void)
{
	int i;

	printf("\nStandard commands:\n");
	i = 0;
	while (*g_standard_commands[i])
		printf("%s\n", g_standard_commands[i++]);
	printf("\nMessage Digest commands:\n");
	i = 0;
	while (*g_md_commands[i])
		printf("%s\n", g_md_commands[i++]);
	printf("\nCipher commands\n");
	i = 0;
	while (*g_cipher_commands[i])
		printf("%s\n", g_cipher_commands[i++]);
	return (0);
}

int		is_command(char *command)
{
	int i;

	i = 0;
	while (g_md_commands[i])
	{
		if (ft_strequ(command, g_md_commands[i++]))
			return (1);
	}
	return (0);
}

int		is_valid_flag(char *command, char *argv, int *flags)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (ft_strchr(FLAGS, argv[i]))
			*flags += pow(2, argv[i++] - 'p');
		else
		{
			printf("%s: illegal option -- %c\n", command, argv[i]);
			return (1);
		}
	}
	return (0);
}
