/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:28:37 by nsondag           #+#    #+#             */
/*   Updated: 2020/10/07 15:35:28 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

int		ft_realloc(void **tab, size_t *size_av,
		size_t new_size_ap, size_t type_size)
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

int64_t	read_all(char **str, int fd)
{
	size_t index;
	size_t size;
	size_t ret;

	size = BUFFER + 1;
	if (!(*str = malloc(size * sizeof(char))))
	{
		printf("malloc error\n");
		return (0);
	}
	index = 0;
	ret = read(fd, *str + index, BUFFER);
	while (ret > 0)
	{
		index += ret;
		(*str)[index] = 0;
		if (ret < BUFFER)
			return (index);
		if (index + BUFFER >= size - 1 &&
				!ft_realloc((void **)str, &size, size * 2, sizeof(char)))
			return (0);
		ret = read(fd, *str + index, BUFFER);
	}
	if (ret < 0)
		return (0);
	return (index);
}

int64_t	parser(char *string, char *file, t_all *all)
{
	int fd;
	int fd2;
	int64_t len;

	len = 0;
	if (all->flags & P)
	{
		read_all(&string, 0);
		close(0);
		if (*string)
			printf("%s", string);
	}
	else if (file && (fd = open(file, O_RDONLY)) == -1)
	{
		printf("md5: %s: No such file or directory\n", file);
		all->listen_flag = 0;
		return (-1);
	}
	else if (file)
	{
		len = read_all(&string, fd);
		if (!len)
		{
			if ((fd2 = open(ft_strcat(file, "/"), O_RDONLY)) != -1)
			{
				printf("md5: %s: Is a directory\n", ft_strsub(file, 0, ft_strlen(file) - 1));
				return (-1);
			}
			file = ft_strsub(file, 0, ft_strlen(file) - 1);
			close(fd2);
		}
		close(fd);
		if (!(all->flags & Q) && !(all->flags & R))
			printf("%s(%s)= ", all->command, file);
		all->listen_flag = 0;
	}
	else if (all->read_entry)
	{
		read_all(&string, 0);
		close(0);
	}
	else
		string = "";
	all->message = string;
	return (len);
}
