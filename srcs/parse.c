/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:28:37 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/27 13:45:01 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"
#include <errno.h>

int		ft_realloc(void **tab, int64_t *size_av,
		int64_t new_size_ap, int64_t type_size)
{
	char	*save;
	int64_t	size;
	int64_t	new_size;

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

int64_t	read_all(char **str, int fd)
{
	int64_t index;
	int64_t size;
	int64_t ret;

	size = BUFFER + 1;
	if (!(*str = malloc(size * sizeof(char))))
		return (0);
	index = 0;
	ft_bzero(*str, size);
	ret = read(fd, *str + index, BUFFER);
	while (ret > 0)
	{
		index += ret;
		(*str)[index] = 0;
		if (index + BUFFER >= size - 1 &&
				!ft_realloc((void **)str, &size, size * 2, sizeof(char)))
			return (0);
		ret = read(fd, *str + index, BUFFER);
	}
	if (ret < 0)
		return (0);
	return (index);
}

int64_t	parse(char *string, char *f, t_all *all)
{
	int		fd;
	int64_t len;

	len = 0;
	if (all->flags & P || (all->read_entry && !f))
		fd = 0;
	else if (f)
	{
		fd = open(f, O_RDONLY);
		all->listen_flag = 0;
	}
	if (errno)
		return (-ft_printf("%s: %s: %s\n", all->command, f, strerror(errno)));
	len = read_all(&string, fd);
	close(fd);
	if (errno)
		return (-ft_printf("%s: %s: %s\n", all->command, f, strerror(errno)));
	if ((!(all->flags & Q) && !(all->flags & R)) && f)
		ft_printf("%s(%s)= ", all->command, f);
	if ((string && all->flags & P) && (!(all->flags & Q) && !(all->flags & R))
			&& !f)
		ft_printf("%s", string);
	all->message = string;
	return (len);
}
