/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 16:38:04 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/21 15:21:40 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	modifier_signed(t_args *args, va_list ap)
{
	if (args->modifier == LL)
		args->value = (long long)va_arg(ap, long long);
	else if (args->modifier == L)
		args->value = (long)va_arg(ap, long);
	else if (args->modifier == J)
		args->value = (intmax_t)va_arg(ap, intmax_t);
	else if (args->modifier == Z)
		args->value = (ssize_t)va_arg(ap, ssize_t);
	else if (args->modifier == H)
		args->value = (short)va_arg(ap, int);
	else if (args->modifier == HH)
		args->value = (char)va_arg(ap, int);
	else
		args->value = (int)va_arg(ap, int);
}

void	modifier_unsigned(t_args *args, va_list ap)
{
	if (args->modifier == LL || args->specifier == 'p')
		args->u_value = (unsigned long long)va_arg(ap, unsigned long long);
	else if (args->modifier == L)
		args->u_value = (unsigned long)va_arg(ap, unsigned long);
	else if (args->modifier == J)
		args->u_value = (uintmax_t)va_arg(ap, uintmax_t);
	else if (args->modifier == Z)
		args->u_value = (size_t)va_arg(ap, size_t);
	else if (args->modifier == H)
		args->u_value = (unsigned short)va_arg(ap, unsigned int);
	else if (args->modifier == HH)
		args->u_value = (unsigned char)va_arg(ap, unsigned int);
	else
		args->u_value = (unsigned int)va_arg(ap, unsigned int);
}
