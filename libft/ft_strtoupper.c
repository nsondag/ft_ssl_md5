/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:22:27 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/19 11:55:16 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtoupper(void *dst, const void *src)
{
	char *dstc;
	char *srcc;

	dstc = (char *)dst;
	srcc = (char *)src;
	while (*srcc)
	{
		*dstc++ = ft_toupper((int)(*srcc++));
	}
}
