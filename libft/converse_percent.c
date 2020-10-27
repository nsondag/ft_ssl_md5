/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converse_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:55:09 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/21 19:53:31 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_size_percent(t_args *args)
{
	int size;

	if (1 < args->fieldwidth)
		size = args->fieldwidth;
	else
		size = 1;
	args->count += size;
	return (size);
}

void	converse_percent(t_args *args)
{
	int size;
	int i;

	i = 0;
	size = get_size_percent(args);
	if (!(args->s = malloc(sizeof(char) * (size + 1))))
		return ;
	i = manage_fieldwidth(args, i, size);
	if (!args->flags['-' - FLAGMIN])
	{
		while (i > args->fieldwidth - 1 && i)
			i--;
	}
	else
		i = 0;
	args->s[i] = '%';
	write(1, args->s, size);
	free(args->s);
}
