/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converse_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 12:53:54 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/22 23:17:27 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_size_c(t_args *args)
{
	int size;

	args->current_count = 1;
	if (args->current_count < args->fieldwidth)
		size = args->fieldwidth;
	else
		size = args->current_count;
	args->count += size;
	return (size);
}

void	converse_c(t_args *args)
{
	int size;
	int i;

	if (args->error && args->modifier)
		return ;
	i = 0;
	size = 0;
	if (args->modifier != L || args->value < 128)
		size = get_size_c(args);
	if (!(args->s = malloc(sizeof(char) * (size + 1))))
		return ;
	i = manage_fieldwidth(args, i, size);
	if (!args->flags['-' - FLAGMIN])
		while (i > args->fieldwidth - args->current_count && i)
			i--;
	else
		i = 0;
	args->s[i] = args->value;
	if (args->modifier == L && args->value >= 128)
		args->count += handle_multibytechar(args, 1);
	else
		write(1, args->s, size);
	if (size > 0)
		free(args->s);
}
