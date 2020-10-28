/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:23:05 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/27 13:46:45 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include "../libft/libft.h"
# include <fcntl.h>

# define BUFFER 10000
# define FLAG "pqrs"
# define P 1
# define Q 2
# define R 4
# define S 8

typedef	struct	s_all
{
	char		*message;
	int			nb_blocks;
	char		*av;
	int			flags;
	char		command[32];
	char		uppercommand[32];
	int			listen_flag;
	int			read_entry;
	int			ac;
	u_int32_t	vars[8];
}				t_all;

/*
 ** GENERAL
*/

u_int32_t		*padding(u_int32_t *block, int64_t len, t_all *all);
int64_t			parse(char *string, char *file, t_all *all);
int				show_commands(void);
int				is_command(t_all *all);
int				is_valid_flag(t_all *all, char *av);
void			get_blocks(t_all *all, u_int32_t	**block, int64_t *len);

/*
 ** SHA256
*/

void			ft_sha256(t_all *all, u_int32_t	**block, int64_t len);
u_int32_t		sigma(u_int32_t x, int i);
u_int32_t		maj(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t		ch(u_int32_t x, u_int32_t y, u_int32_t z);

/*
 ** MD5
*/

void			ft_md5(t_all *all, u_int32_t	**block, int64_t len);
u_int32_t		func_f(u_int32_t abcd[4]);
u_int32_t		func_g(u_int32_t abcd[4]);
u_int32_t		func_h(u_int32_t abcd[4]);
u_int32_t		func_i(u_int32_t abcd[4]);

/*
 ** SHIFTS
*/

u_int32_t		left_shift(u_int32_t a, int s);
u_int32_t		right_rot(u_int32_t a, int s);
u_int32_t		left_rot(u_int32_t a, int s);
u_int32_t		rev_int_byte(u_int32_t nbr);

#endif
