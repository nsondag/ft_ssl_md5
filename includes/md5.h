/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:23:05 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/18 12:47:01 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <fcntl.h>

# define BUFFER 10000
# define FLAGS "pqrs"
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
	char		command[256];
	int			listen_flag;
	int			read_entry;
	int			ac;
	uint32_t	vars[8];
}				t_all;

/*
 ** GENERAL
*/

uint32_t		*padding(uint32_t *block, int64_t len, t_all *all);
void			init_all(t_all *all);
long long		parser(char *string, char *file, t_all *all);
int				show_commands(void);
int				is_command(char *command);
int				is_valid_flag(t_all *all, char *av);
void			get_blocks(t_all *all, uint32_t	**block, int64_t *len);

/*
 ** SHA256
*/

void			ft_sha256(t_all *all, uint32_t	**block, int64_t len);
uint32_t		sigma(uint32_t x, int i);
uint32_t		maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t		ch(uint32_t x, uint32_t y, uint32_t z);

/*
 ** MD5
*/

void			ft_md5(t_all *all, uint32_t	**block, int64_t len);
uint32_t		func_f(uint32_t abcd[4]);
uint32_t		func_g(uint32_t abcd[4]);
uint32_t		func_h(uint32_t abcd[4]);
uint32_t		func_i(uint32_t abcd[4]);

/*
 ** SHIFTS
*/

uint32_t		left_shift(uint32_t a, int s);
uint32_t		right_rot(uint32_t a, int s);
uint32_t		left_rot(uint32_t a, int s);
uint32_t		rev_int_byte(uint32_t nbr);

#endif
