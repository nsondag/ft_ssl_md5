/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:48:33 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/15 20:48:38 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"
/* Padding:
  Message must have a length multiple of 512 and contain the length
  of the original message
  First add a 1 bit after the message, then 0 until multiple of 512,
  except for the last 64 bits who will contain de original length of the message
*/

unsigned char *padding(char *message)
{
  unsigned char *padded_message;
  int init_len;
  int new_len;
  int i = 0;

  padded_message = malloc(128 * sizeof(*padded_message));
  bzero(padded_message, 128);
  init_len = strlen(message);
  memcpy(padded_message, message, init_len);
  padded_message[init_len] = 0b10000000;
  uint32_t bits_len = 8 * init_len; // need to be inversed?
  i = 0;
  memcpy(padded_message + 56, &bits_len, 8);// in bits at the end of the buffer
  new_len = strlen((char*)padded_message);
  new_len = ((((init_len + 8) / 64) + 1) * 64) - 8; // need explanation
  memcpy(padded_message + new_len, &bits_len, 4); //idem
  return (padded_message);
}

uint32_t r1(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, int s, int i, unsigned long tab[64])
{
  a = (b + left_rot((a + func_f(b, c, d) + x + tab[i - 1]), s));
  return (a);
}

uint32_t r2(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, int s, int i, unsigned long tab[64])
{
  a = (b + left_rot(a + func_g(b, c, d) + x + tab[i - 1], s));
  return (a);
}

uint32_t r3(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, int s, int i, unsigned long tab[64])
{
  a = (b + left_rot(a + func_h(b, c, d) + x + tab[i - 1], s));
  return (a);
}

uint32_t r4(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, int s, int i, unsigned long tab[64])
{
  a = (b + left_rot((a + func_i(b, c, d) + x + tab[i - 1]), s));
  return (a);
}

uint32_t ft_md5(unsigned char *string)
{
  uint32_t a = 0x67452301;
  uint32_t b = 0xefcdab89;
  uint32_t c = 0x98badcfe;
  uint32_t d = 0x10325476;
  //int i = 0;
  int j = 0;
  int l = 0;
  uint32_t tmp_a = 0;
  uint32_t tmp_b = 0;
  uint32_t tmp_c = 0;
  uint32_t tmp_d = 0;
  uint32_t x[16] = {128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //''
  //uint32_t x[16] = {1819043144, 1867980911, 1063545970, 1819043144, 1867980911, 744778866,
  //  1699233568, 544173164, 1819438935, 1059073124, 1819043144, 1867980911, 744778866, 8404768, 432, 0};// "Hello World?Hello World, ?Hello World, ?Hello World, ?"
  //int s1[4] = {7, 12, 17, 22};
  //int s2[4] = {5, 9, 14, 20};
  //int s3[4] = {4, 11, 16, 23};
  //int s4[4] = {6, 10, 15, 21};
  (void)string;
  unsigned long tab[64];
  while (l < 64)
  {
    tab[l] = (unsigned long)(fabs(sin(l + 1)) * pow(2, 32));
    l++;
  }
  //while (i < 512)
  //{
      tmp_a = a;
      tmp_b = b;
      tmp_c = c;
      tmp_d = d;
      j = 0;
      //while(j < 16)
      //{
        //printf("j: %d\n", j);
        //printf("i mod 32 %d\n", i % 32);
        //x[j][i % 32] = string[i * 16 + j];
        //x[j][i % 32] = 0;
        //j++;
      //}
      //i++;
  //}
  a = r1(a, b, c, d, x[0], 7, 1, tab);
  d = r1(d, a, b, c, x[1], 12, 2, tab);
  c = r1(c, d, a, b, x[2], 17, 3, tab);
  b = r1(b, c, d, a, x[3], 22, 4, tab);
  a = r1(a, b, c, d, x[4], 7, 5, tab);
  d = r1(d, a, b, c, x[5], 12, 6, tab);
  c = r1(c, d, a, b, x[6], 17, 7, tab);
  b = r1(b, c, d, a, x[7], 22, 8, tab);
  a = r1(a, b, c, d, x[8], 7, 9, tab);
  d = r1(d, a, b, c, x[9], 12, 10, tab);
  c = r1(c, d, a, b, x[10], 17, 11, tab);
  b = r1(b, c, d, a, x[11], 22, 12, tab);
  a = r1(a, b, c, d, x[12], 7, 13, tab);
  d = r1(d, a, b, c, x[13], 12, 14, tab);
  c = r1(c, d, a, b, x[14], 17, 15, tab);
  b = r1(b, c, d, a, x[15], 22, 16, tab);

  a = r2(a, b, c, d, x[1], 5, 17, tab);
  d = r2(d, a, b, c, x[6], 9, 18, tab);
  c = r2(c, d, a, b, x[11], 14, 19, tab);
  b = r2(b, c, d, a, x[0], 20, 20, tab);
  a = r2(a, b, c, d, x[5], 5, 21, tab);
  d = r2(d, a, b, c, x[10], 9, 22, tab);
  c = r2(c, d, a, b, x[15], 14, 23, tab);
  b = r2(b, c, d, a, x[4], 20, 24, tab);
  a = r2(a, b, c, d, x[9], 5, 25, tab);
  d = r2(d, a, b, c, x[14], 9, 26, tab);
  c = r2(c, d, a, b, x[3], 14, 27, tab);
  b = r2(b, c, d, a, x[8], 20, 28, tab);
  a = r2(a, b, c, d, x[13], 5, 29, tab);
  d = r2(d, a, b, c, x[2], 9, 30, tab);
  c = r2(c, d, a, b, x[7], 14, 31, tab);
  b = r2(b, c, d, a, x[12], 20, 32, tab);

  a = r3(a, b, c, d, x[5], 4, 33, tab);
  d = r3(d, a, b, c, x[8], 11, 34, tab);
  c = r3(c, d, a, b, x[11], 16, 35, tab);
  b = r3(b, c, d, a, x[14], 23, 36, tab);
  a = r3(a, b, c, d, x[1], 4, 37, tab);
  d = r3(d, a, b, c, x[4], 11, 38, tab);
  c = r3(c, d, a, b, x[7], 16, 39, tab);
  b = r3(b, c, d, a, x[10], 23, 40, tab);
  a = r3(a, b, c, d, x[13], 4, 41, tab);
  d = r3(d, a, b, c, x[0], 11, 42, tab);
  c = r3(c, d, a, b, x[3], 16, 43, tab);
  b = r3(b, c, d, a, x[6], 23, 44, tab);
  a = r3(a, b, c, d, x[9], 4, 45, tab);
  d = r3(d, a, b, c, x[12], 11, 46, tab);
  c = r3(c, d, a, b, x[15], 16, 47, tab);
  b = r3(b, c, d, a, x[2], 23, 48, tab);

  a = r4(a, b, c, d, x[0], 6, 49, tab);
  d = r4(d, a, b, c, x[7], 10, 50, tab);
  c = r4(c, d, a, b, x[14], 15, 51, tab);
  b = r4(b, c, d, a, x[5], 21, 52, tab);
  a = r4(a, b, c, d, x[12], 6, 53, tab);
  d = r4(d, a, b, c, x[3], 10, 54, tab);
  c = r4(c, d, a, b, x[10], 15, 55, tab);
  b = r4(b, c, d, a, x[1], 21, 56, tab);
  a = r4(a, b, c, d, x[8], 6, 57, tab);
  d = r4(d, a, b, c, x[15], 10, 58, tab);
  c = r4(c, d, a, b, x[6], 15, 59, tab);
  b = r4(b, c, d, a, x[13], 21, 60, tab);
  a = r4(a, b, c, d, x[4], 6, 61, tab);
  d = r4(d, a, b, c, x[11], 10, 62, tab);
  c = r4(c, d, a, b, x[2], 15, 63, tab);
  b = r4(b, c, d, a, x[9], 21, 64, tab);

a = a + tmp_a;
b = b + tmp_b;
c = c + tmp_c;
d = d + tmp_d;
printf("%u | %x\n", a, a);
printf("%u | %x\n", b, b);
printf("%u | %x\n", c, c);
printf("%u | %x\n", d, d);
// for result convert a, b, c, d to little endian and add them as a string
return (0);
}

int main(int argc, char **argv)
{
  unsigned char *result;

  if (argc < 2)
  {
      write(2, "usage\n", 6);
      return (0);
  }
  else
  {
      //printf("%s\n", argv[1]);
      result = padding(argv[1]);
      //printf("%s\n", argv[1]);
      ft_md5(result);
      //printf("%s\n", result);
  }
  return (0);
}
