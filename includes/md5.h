/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:23:05 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/20 14:23:07 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

uint32_t left_rot(uint32_t a, int s);
uint32_t func_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t func_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t func_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t func_i(uint32_t x, uint32_t y, uint32_t z);
unsigned char *padding(char *message);
uint32_t r1(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, int s, int i, unsigned long tab[64]);
uint32_t r2(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, int s, int i, unsigned long tab[64]);
uint32_t r3(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, int s, int i, unsigned long tab[64]);
uint32_t r4(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, int s, int i, unsigned long tab[64]);
uint32_t ft_md5(unsigned char *string);
#endif
