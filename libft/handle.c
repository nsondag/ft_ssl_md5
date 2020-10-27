/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 16:04:40 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/22 23:50:37 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		handle_conversion(t_args *args, va_list ap)
{
	if (ft_strchr(SIGNED_SPECIFIER, args->specifier))
	{
		modifier_signed(args, ap);
		converse_d(args);
	}
	else if (ft_strchr(UNSIGNED_SPECIFIER, args->specifier))
	{
		modifier_unsigned(args, ap);
		converse_u(args);
	}
	else if (args->specifier == '%')
		converse_percent(args);
	else if (args->specifier == 'c')
	{
		args->modifier == L ? (args->value = (wchar_t)va_arg(ap, int)) :
			(args->value = (char)va_arg(ap, int));
		if (args->modifier == L && (args->value < 0 ||
					(MB_CUR_MAX < 2 && args->value > 127)))
			args->error = 1;
		converse_c(args);
	}
	else if (args->specifier == 's')
		args->modifier == L ? converse_ws(args, ap) : converse_s(args, ap);
}

static char	*nbr_byte(t_args *a, char *byte, int *len)
{
	if (a->value < 0x0080)
		byte[0] = a->value;
	else if (a->value < 0x0800)
	{
		byte[1] = (a->value & 0b111111) + 0b10000000;
		byte[0] = ((a->value >> 6) & 0b111111) + 0b11000000;
		*len += 1;
	}
	else if (a->value < 0x10000)
	{
		byte[2] = (a->value & 0b111111) + 0b10000000;
		byte[1] = ((a->value >> 6) & 0b111111) + 0b10000000;
		byte[0] = ((a->value >> 12) & 0b111111) + 0b11100000;
		*len += 2;
	}
	else if (a->value <= 0x10FFFF)
	{
		byte[3] = (a->value & 0b111111) + 0b10000000;
		byte[2] = ((a->value >> 6) & 0b111111) + 0b10000000;
		byte[1] = ((a->value >> 12) & 0b111111) + 0b10000000;
		byte[0] = ((a->value >> 18) & 0b111111) + 0b11110000;
		*len += 3;
	}
	(a->value > 0x10FFFF) ? a->error = 1 : 0;
	return (byte);
}

static void	fieldpadding_wc(t_args *args, int len, char *byte)
{
	if (!args->flags['-' - FLAGMIN])
	{
		while (args->fieldwidth-- > len)
			(args->flags['0' - FLAGMIN]) ? write(1, "0", 1) : write(1, " ", 1);
		write(1, byte, len);
	}
	else
	{
		write(1, byte, len);
		while (args->fieldwidth-- > len)
			write(1, " ", 1);
	}
}

int			handle_multibytechar(t_args *args, int to_write)
{
	char	byte[4];
	int		len;

	len = 1;
	if ((args->value >= 0xD800 && args->value < 0xE000) || args->error)
	{
		args->error = 1;
		return (0);
	}
	else
		args->s = nbr_byte(args, byte, &len);
	if ((args->precision >= len || args->precision < 0) &&
			args->specifier == 's')
		(!to_write) ? args->stringlen += len : write(1, byte, len);
	else if (!to_write)
		args->count -= len;
	if (args->specifier == 'c')
	{
		args->count += (args->fieldwidth > len ? args->fieldwidth : len);
		fieldpadding_wc(args, len, byte);
		return (0);
	}
	return (len - 1);
}
