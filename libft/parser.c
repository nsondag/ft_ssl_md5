/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 16:42:56 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/21 14:26:24 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*search_flags(char *current_arg, t_args *args)
{
	int i;

	i = 0;
	while (i < FLAGMAX)
		args->flags[i++] = 0;
	while (ft_strchr(FLAGS, *current_arg))
	{
		args->flags[*current_arg - FLAGMIN] += 1;
		current_arg++;
	}
	if (args->flags['+' - FLAGMIN] > 0)
		args->flags[' ' - FLAGMIN] = 0;
	if (args->flags['-' - FLAGMIN] > 0)
		args->flags['0' - FLAGMIN] = 0;
	return (current_arg);
}

static char		*search_fieldwidth(char *current_arg, t_args *args)
{
	int fieldwidth;

	args->fieldwidth = 0;
	fieldwidth = ft_atoi(current_arg);
	if (fieldwidth > 0)
		args->fieldwidth = fieldwidth;
	while (ft_isdigit(*current_arg))
		current_arg++;
	return (current_arg);
}

static char		*search_precision(char *current_arg, t_args *args)
{
	args->precision = -1;
	if (*current_arg == '.')
	{
		args->precision = 0;
		current_arg++;
		args->precision = ft_atoi(current_arg);
		while (ft_isdigit(*current_arg))
			current_arg++;
	}
	return (current_arg);
}

static char		*search_modifier(char *current_arg, t_args *args)
{
	int		i;
	char	*tab[6];

	args->modifier = 0;
	i = 0;
	tab[0] = "hh";
	tab[1] = "ll";
	tab[2] = "h";
	tab[3] = "l";
	tab[4] = "j";
	tab[5] = "z";
	while (i < 6 && args->modifier == 0)
	{
		if (ft_strstr(current_arg, tab[i]))
			args->modifier = i + 1;
		i++;
	}
	return (current_arg);
}

void			parser(char *current_arg, t_args *args)
{
	current_arg = search_flags(current_arg, args);
	current_arg = search_fieldwidth(current_arg, args);
	current_arg = search_precision(current_arg, args);
	search_modifier(current_arg, args);
}
