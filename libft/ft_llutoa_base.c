/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llutoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:04:30 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/09 21:11:23 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	convu(uintmax_t value, char uppercase)
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

void		ft_llutoa_base(t_args *args, int i)
{
	int		begin;
	int		end;
	int		digit;

	if (args->base < 2 || args->base > 16)
		return ;
	begin = i;
	end = begin + u_count(args->u_value, args->base) - 1;
	while (end >= begin)
	{
		digit = args->u_value % args->base;
		args->s[end] = convu(digit, args->specifier);
		args->u_value /= args->base;
		end--;
	}
}
