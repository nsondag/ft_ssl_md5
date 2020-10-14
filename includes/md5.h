/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:23:05 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/20 18:36:30 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>

# define BUFFER 100000
# define A 0x67452301
# define B 0xefcdab89
# define C 0x98badcfe
# define D 0x10325476
# define H1 0x6a09e667
# define H2 0xbb67ae85
# define H3 0x3c6ef372
# define H4 0xa54ff53a
# define H5 0x510e527f
# define H6 0x9b05688c
# define H7 0x1f83d9ab
# define H8 0x5be0cd19
# define FLAGS "pqrs"
# define P 1
# define Q 2
# define R 4
# define S 8

union	u_word
{
	unsigned char  tab[4];
	uint32_t         x;
}		word;

typedef struct s_md5
{
	unsigned long tab[64];
	int **s;
	uint32_t abcd[4];
}	t_md5;

typedef struct s_sha256
{
	unsigned long tab[64];
	int **s;
	uint32_t abcd[4];
}	t_sha256;

typedef struct s_all
{
	char *message;
	int nb_blocks;
	char	*av;
	int		flags;
	char	command[256];
	int		listen_flag;
	int   read_entry;
	int		ac;
	t_md5	md5_vars;
	t_sha256 sha256_vars;
}	t_all;

uint32_t sum1(uint32_t x);
uint32_t sum2(uint32_t x);
uint32_t sum3(uint32_t x);
uint32_t sum4(uint32_t x);
uint32_t maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t	left_shift(uint32_t a, int s);
uint32_t	right_rot(uint32_t a, int s);
union u_word *prepare_sha256(union u_word *word);
void			process_sha256(t_all *all, union u_word	**block);
void			get_blocks(t_all *all, union u_word	**block, int *len);
uint32_t	*ft_sha256(union u_word word[64]);

void init_tab(t_md5 *vars);
void init_s(t_md5 *vars);
void init_all(t_all *all);
void init_md5(t_md5 *vars);
void init_sha256(t_sha256 *vars);
uint32_t *ft_md5(union u_word word[16], t_md5 *vars);

uint32_t left_rot(uint32_t a, int s);
uint32_t func_f(uint32_t abcd[4]);
uint32_t func_g(uint32_t abcd[4]);
uint32_t func_h(uint32_t abcd[4]);
uint32_t func_i(uint32_t abcd[4]);
int 		 parser(char *string, char *file, t_all *all);
int		show_commands(void);
int is_command(char *command);
int is_valid_flag(t_all *all, char *av);
void			get_blocks(t_all *all, union u_word	**block, int *len);
uint32_t		rev_int_byte(uint32_t nbr);
#endif
