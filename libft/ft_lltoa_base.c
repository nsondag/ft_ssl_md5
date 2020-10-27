/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:04:30 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/09 20:58:35 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	conv(intmax_t value, char uppercase)
{
	char nbr;

	if (value < 10)
		nbr = value + '0';
	else if (uppercase == 'X')
		nbr = value + 'A' - 10;
	else
		nbr = value + 'a' - 10;
	return (nbr);
}

void		ft_lltoa_base(t_args *args, int i)
{
	int		begin;
	int		end;
	int		digit;

	if (args->base < 2 || args->base > 16)
		return ;
	begin = i;
	end = begin + count(args->value, args->base) - 1;
	if (args->value < 0)
	{
		if (args->value < -9223372036854775807 && args->base == 10)
		{
			args->s[begin] = 9 + '0';
			args->value = 223372036854775808;
		}
		else
			args->value *= -1;
	}
	while (end >= begin && args->s[end] != 9 + '0')
	{
		digit = args->value % args->base;
		args->s[end] = conv(digit, args->specifier);
		args->value /= args->base;
		end--;
	}
}
