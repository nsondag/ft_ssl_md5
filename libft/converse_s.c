/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converse_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 11:33:03 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/22 23:52:16 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	converse_s(t_args *args, va_list ap)
{
	int		size;
	int		padding;

	padding = 0;
	args->s = (char*)va_arg(ap, char*);
	if (!args->s)
		args->s = "(null)";
	size = sp_strlen(args->s);
	if (args->precision < size && args->precision >= 0)
		size = args->precision;
	if (args->fieldwidth > size)
		padding = args->fieldwidth - size;
	args->count += size + padding;
	if (args->flags['-' - FLAGMIN])
	{
		write(1, args->s, size);
		while (padding-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (padding-- > 0)
			(args->flags['0' - FLAGMIN]) ? write(1, "0", 1) : write(1, " ", 1);
		write(1, args->s, size);
	}
}
