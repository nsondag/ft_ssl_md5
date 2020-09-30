/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:28:37 by nsondag           #+#    #+#             */
/*   Updated: 2020/09/28 15:28:39 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

int				ft_realloc(void **tab, int *size_av,
		int new_size_ap, size_t type_size)
{
	char			*save;
	unsigned int	size;
	unsigned int	new_size;

	size = *size_av;
	new_size = new_size_ap;
	if (new_size == size)
		return (1);
	if (!(save = malloc(new_size * type_size)))
		return (0);
	if (size)
	{
		ft_memcpy(save, *tab, size * type_size);
		free(*tab);
	}
	*tab = save;
	if (new_size > size)
		ft_memset(*tab + size, 0, (new_size - size) * type_size);
	*size_av = new_size;
	return (1);
}

int			read_all(char **str, int fd)
{
	int index;
	int size;
	int ret;

	size = 28000 + 1;
	if (!(*str = malloc(size * sizeof(char))))
		return(0);
	index = 0;
  ret = read(fd, *(str + index), 28000);
	while (ret > 0)
	{
		index += ret;
		(*str)[index] = 0;
		if (ret < 28000)
			return (index);
		if (index + 28000 >= size - 1 &&
		!ft_realloc((void **)str, &size, size * 2, sizeof(char)))
			return (0);
    ret = read(fd, *(str + index), 28000);
	}
	if (ret < 0)
		return (0);
	return (index);
}

int parser(char *string, char *file, t_md5 *vars, t_all *all)
{
  int fd;

	if (all->flags & P)
	{
		read_all(&string, 0);
		all->flags -= P;
	}
  else if ((fd = open(file, O_RDONLY)) == -1)
	{
		printf("md5: %s: No such file or directory\n", file);
		return (0);
	}
  else
    read_all(&string, fd);
  vars->message = string;
  return (1);
}
