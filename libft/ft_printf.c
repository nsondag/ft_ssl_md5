/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 18:30:30 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/22 22:21:21 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			get_base(t_args *args)
{
	if (args->specifier == 'x' || args->specifier == 'X'
			|| args->specifier == 'p')
		args->base = 16;
	else if (args->specifier == 'o')
		args->base = 8;
	else
		args->base = 10;
}

static void			flag_no_effect(t_args *args)
{
	if (args->specifier == 'u')
	{
		args->flags['+' - FLAGMIN] = 0;
		args->flags[' ' - FLAGMIN] = 0;
	}
	else if (args->specifier == '%')
	{
		args->flags['+' - FLAGMIN] = 0;
		args->flags['#' - FLAGMIN] = 0;
	}
	else if (args->specifier != 'i' && args->specifier != 'd')
	{
		args->flags[' ' - FLAGMIN] = 0;
		args->flags['+' - FLAGMIN] = 0;
	}
}

static void			adapt_param(t_args *args)
{
	if (ft_strchr(L_SPECIFIER, args->specifier))
	{
		args->modifier = L;
		args->specifier += 'a' - 'A';
	}
	else if (args->specifier == 'p')
	{
		args->flags['#' - FLAGMIN] = 1;
		args->modifier = LL;
	}
	if (args->precision > 0 && args->specifier != '%')
		args->flags['0' - FLAGMIN] = 0;
	else if (!args->precision && args->flags['0' - FLAGMIN] &&
			(args->specifier == 'o' || args->specifier == 'x'
			|| args->specifier == 'X'))
		args->flags['0' - FLAGMIN] = 0;
	if (args->specifier == 'o' && !args->precision &&
		args->flags['#' - FLAGMIN])
		args->precision = -1;
	flag_no_effect(args);
}

static const char	*dispatch(const char *format, t_args *args, va_list ap)
{
	int		i;
	char	*current_arg;

	i = 0;
	while (!ft_strchr(SPECIFIER, format[i]) && format[i] &&
			(ft_isdigit(format[i]) || ft_strchr(FLAGS, format[i])
			|| ft_strchr(OPTIONS, format[i])))
		i++;
	if (format[i])
	{
		current_arg = ft_strsub(format, 0, i + 1);
		parser(current_arg, args);
		free(current_arg);
		args->specifier = format[i];
		adapt_param(args);
		get_base(args);
		handle_conversion(args, ap);
		if (ft_strchr(SPECIFIER, format[i]))
			format++;
		format = format + i;
	}
	return (format);
}

int					ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	t_args		args;

	va_start(ap, format);
	args.error = 0;
	args.count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			format = dispatch(format, &args, ap);
			if (args.error > 0)
				return (-1);
		}
		else
		{
			ft_putchar(*format++);
			args.count++;
		}
	}
	va_end(ap);
	return (args.count);
}
