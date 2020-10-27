/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converse_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:42:06 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/22 22:21:54 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_size_d(t_args *args)
{
	int size;

	if (args->value || args->precision)
		args->current_count = count(args->value, args->base);
	else
		args->current_count = 0;
	if (args->precision > args->current_count)
		args->current_count = args->precision;
	if (args->flags[' ' - FLAGMIN] || args->flags['+' - FLAGMIN]
			|| args->value < 0)
		args->current_count++;
	if (args->current_count < args->fieldwidth)
		size = args->fieldwidth;
	else
		size = args->current_count;
	args->count += size;
	return (size);
}

int		manage_flags_d(t_args *args, int i)
{
	if (args->value < 0)
		args->s[i++] = '-';
	else if (args->flags[' ' - FLAGMIN])
		args->s[i++] = ' ';
	else if (args->flags['+' - FLAGMIN])
		args->s[i++] = '+';
	return (i);
}

int		manage_fieldwidth(t_args *args, int i, int size)
{
	i = 0;
	while (i < size)
	{
		if (args->flags['0' - FLAGMIN])
			args->s[i++] = '0';
		else
			args->s[i++] = ' ';
	}
	return (i);
}

int		manage_precision(t_args *args, int i)
{
	if (args->precision <= 0)
		return (i);
	while (args->precision > count(args->value, args->base))
	{
		args->s[i++] = '0';
		args->precision--;
	}
	return (i);
}

void	converse_d(t_args *args)
{
	size_t	size;
	int		i;

	i = 0;
	size = get_size_d(args);
	if (!(args->s = malloc(sizeof(char) * (size + 1))))
		return ;
	i = manage_fieldwidth(args, i, size);
	if (!args->flags['-' - FLAGMIN])
	{
		while (i > args->fieldwidth - args->current_count && i)
			i--;
	}
	else
		i = 0;
	if (args->flags['0' - FLAGMIN])
		manage_flags_d(args, 0) ? i++ : 0;
	else
		i = manage_flags_d(args, i);
	i = manage_precision(args, i);
	if (args->value || args->precision)
		ft_lltoa_base(args, i);
	write(1, args->s, size);
	free(args->s);
}
