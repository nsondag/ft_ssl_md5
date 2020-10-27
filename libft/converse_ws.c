/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converse_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:23:50 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/22 21:58:58 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		loop_on_ws(t_args *args, int to_write, int size)
{
	int i;
	int	size_char;

	i = 0;
	while (args->ws[i])
	{
		args->value = args->ws[i++];
		if (args->precision < 0)
			size += handle_multibytechar(args, to_write) + 1;
		else
		{
			while (args->precision >= 0 && args->value)
			{
				size_char = handle_multibytechar(args, to_write) + 1;
				size += size_char;
				args->precision -= size_char;
				args->value = args->ws[i++];
			}
			break ;
		}
	}
	return (size);
}

int		ft_strlenw(t_args *args, int to_write)
{
	int size;
	int precision;
	int len;

	precision = args->precision;
	args->stringlen = 0;
	size = 0;
	if (!args->ws)
	{
		if (precision > 6 || precision < 0)
			len = 6;
		else
			len = precision;
		to_write ? write(1, "(null)", len) : 0;
		args->stringlen = len;
		return (len);
	}
	size = loop_on_ws(args, to_write, size);
	args->precision = precision;
	return (size);
}

void	converse_ws(t_args *args, va_list ap)
{
	int		size;
	int		padding;

	padding = 0;
	args->ws = (wchar_t*)va_arg(ap, wchar_t*);
	size = ft_strlenw(args, 0);
	if (args->fieldwidth > args->stringlen)
		padding = args->fieldwidth - args->stringlen;
	args->count += size + padding;
	if (args->flags['-' - FLAGMIN])
	{
		ft_strlenw(args, 1);
		while (padding-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (padding-- > 0)
			(args->flags['0' - FLAGMIN]) ? write(1, "0", 1) : write(1, " ", 1);
		ft_strlenw(args, 1);
	}
}
