/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 18:30:45 by nsondag           #+#    #+#             */
/*   Updated: 2018/10/22 17:17:39 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

# define SPECIFIER	"sSpdDioOuUxXcC%"
# define L_SPECIFIER "SDOUC"
# define SIGNED_SPECIFIER "di"
# define UNSIGNED_SPECIFIER "uoxXp"
# define FLAGS		" 0#-+"
# define FLAGMAX 17
# define FLAGMIN ' '
# define OPTIONS ".hljz"

# define HH 1
# define LL 2
# define H 3
# define L 4
# define J 5
# define Z 6

typedef struct	s_args
{
	int			flags[FLAGMAX];
	int			fieldwidth;
	int			precision;
	int			modifier;
	char		specifier;
	uintmax_t	u_value;
	intmax_t	value;
	int			base;
	int			count;
	int			current_count;
	char		*s;
	wchar_t		*ws;
	int			stringlen;
	int			error;
}				t_args;

int				ft_printf(const char *restrict format, ...);
void			parser(char *current_arg, t_args *args);
void			ft_lltoa_base(t_args *args, int i);
void			ft_llutoa_base(t_args *args, int i);
int				ft_strlenw(t_args *args, int to_write);
void			converse_d(t_args *args);
void			converse_s(t_args *args, va_list ap);
void			converse_ws(t_args *args, va_list ap);
void			converse_c(t_args *args);
void			converse_u(t_args *args);
void			converse_percent(t_args *args);
int				manage_fieldwidth(t_args *args, int i, int size);
int				manage_precision(t_args *args, int i);
void			handle_conversion(t_args *args, va_list ap);
int				handle_multibytechar(t_args *args, int to_write);
void			modifier_unsigned(t_args *args, va_list ap);
void			modifier_signed(t_args *args, va_list ap);

#endif
