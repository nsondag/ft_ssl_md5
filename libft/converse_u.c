/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 20:22:54 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/22 13:28:00 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_size_u(t_args *a)
{
	int size;

	if (a->u_value || (a->precision > 1 || a->precision < 0))
		a->current_count = u_count(a->u_value, a->base);
	else
		a->current_count = 0;
	if (a->flags['#' - FLAGMIN] && a->specifier == 'o'
			&& (a->u_value || (a->precision >= 0 &&
			a->precision + 1 > a->fieldwidth && a->fieldwidth > 0)))
		a->current_count++;
	if (a->precision > a->current_count - 1)
	{
		a->current_count = a->precision;
		if (a->flags['#' - FLAGMIN] && a->specifier == 'o' && a->u_value)
			a->precision--;
	}
	if (a->flags['#' - FLAGMIN] && ((a->u_value && (a->specifier == 'x'
						|| a->specifier == 'X')) || a->specifier == 'p'))
		a->current_count += 2;
	size = a->current_count < a->fieldwidth ? a->fieldwidth : a->current_count;
	a->count += size;
	return (size);
}

static int		manage_flags_u(t_args *a, int i)
{
	if (a->specifier == 'o')
	{
		if ((a->fieldwidth <= 0 || a->precision < a->current_count) &&
			(a->u_value || a->fieldwidth <= a->precision + 1))
			a->s[i++] = '0';
		if (a->fieldwidth > 0 && a->precision >= a->current_count)
		{
			if (a->precision++ > 0)
			{
				if (a->fieldwidth > a->precision && !a->flags['-' - FLAGMIN])
					i--;
			}
			if (a->fieldwidth > a->precision && !a->flags['-' - FLAGMIN])
				i++;
			else if (!a->u_value)
				a->precision--;
		}
	}
	else if (((a->specifier == 'x' || a->specifier == 'X')
				&& a->u_value) || a->specifier == 'p')
	{
		a->s[i++] = '0';
		a->s[i++] = a->specifier == 'p' ? 'x' : a->specifier;
	}
	return (i);
}

static int		manage_precision_u(t_args *args, int i)
{
	if (args->precision <= 0)
		return (i);
	while (args->precision > u_count(args->u_value, args->base))
	{
		args->s[i++] = '0';
		args->precision--;
	}
	return (i);
}

static int		fieldwidth_padd_d(t_args *args, int size)
{
	int i;

	i = 0;
	i = manage_fieldwidth(args, i, size);
	if (!args->flags['-' - FLAGMIN])
	{
		while (i > args->fieldwidth - args->current_count && i)
			i--;
	}
	else
		i = 0;
	return (i);
}

void			converse_u(t_args *args)
{
	int size;
	int i;

	size = get_size_u(args);
	if (!(args->s = malloc(sizeof(char) * (size + 1))))
		return ;
	i = fieldwidth_padd_d(args, size);
	if (args->flags['#' - FLAGMIN] && args->flags['0' - FLAGMIN] &&
			(args->specifier == 'o' || args->specifier == 'u'))
		manage_flags_u(args, 0) ? i++ : 0;
	else if (args->flags['#' - FLAGMIN] && args->flags['0' - FLAGMIN]
			&& (args->specifier == 'x' || args->specifier == 'X'
				|| args->specifier == 'p'))
		manage_flags_u(args, 0) ? i += 2 : 0;
	else if (args->flags['#' - FLAGMIN])
		i = manage_flags_u(args, i);
	i = manage_precision_u(args, i);
	if ((args->u_value || args->flags['#' - FLAGMIN]) || args->precision)
		ft_llutoa_base(args, i);
	write(1, args->s, size);
	free(args->s);
}
