/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:50:58 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/14 14:51:00 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

uint32_t	*ft_sha256(union u_word word[64])
{
  uint32_t k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
                    0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
                    0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
                    0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
                    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
                    0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
                    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
                    0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
                    0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
                    0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
                    0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
                    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };
  uint32_t tmp_h[8] = {H1, H2, H3, H4, H5, H6, H7, H8};
  uint32_t *h;
	int			i;
  uint32_t t1;
  uint32_t t2;
  uint32_t test;
  int	shift;

  printf("%u\n", left_shift(31416, 3));
  printf("%u\n", right_rot(31416, 3));
  printf("%u\n", left_rot(31416, 3));

  if (!(h = malloc(8 * sizeof(*h))))
		return (NULL);
  i = -1;
  while (++i < 8)
  {
    h[i] = tmp_h[i];
  }
  i = 0;
  while (i < 64)
  {
    printf("%x ", word[i].x);
    printf("%c ", word[i].tab[0]);
    printf("%c ", word[i].tab[1]);
    printf("%c ", word[i].tab[2]);
    printf("%c\n", word[i].tab[3]);
    i++;
  }
	i = -1;
	while (++i < 64)
	{
      t1 = tmp_h[7] + sum2(tmp_h[4]) + ch(tmp_h[4], tmp_h[5], tmp_h[6]) + k[i] + word[i].x;
      t2 = sum1(tmp_h[0]) + maj(tmp_h[0], tmp_h[1], tmp_h[2]);
      tmp_h[7] = tmp_h[6];
      tmp_h[6] = tmp_h[5];
      tmp_h[5] = tmp_h[4];
      tmp_h[4] = tmp_h[3] + t1;
      tmp_h[3] = tmp_h[2];
      tmp_h[2] = tmp_h[1];
      tmp_h[1] = tmp_h[0];
      tmp_h[0] = t1 + t2;
	}
	i = -1;
	while (++i < 8)
  {
		h[i] = h[i] + tmp_h[i];
    printf("h[%d] = %x\n", i, h[i]);
  }
	return (h);
}
