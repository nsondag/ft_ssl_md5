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
#include <errno.h>

int64_t	parser(char *string, char *file, t_all *all)
{
	int fd;
	int64_t len;
	int			ret;

	len = 0;
	if (all->flags & P || (all->read_entry && !file))
	{
		fd = 0;
		if (string && *string)
			printf("%s", string);
	}
	else if (file)
		fd = open(file, O_RDONLY);
	if (errno)
		return(-printf("%s: %s: %s\n", all->command, file, strerror(errno)));
	if (!(all->message = malloc(512 * sizeof(char))))
		return (0);
	while ((ret = read(fd, all->message, 512)) >= 0)
	{
		len += ret;
		if (fd && len < 512)
			break ;
		if (!all->message[len - 1])
			break ;
	}
	close(fd);
	if (errno)
		return(-printf("%s: %s: %s\n", all->command, file, strerror(errno)));
	all->listen_flag = 0;
	return (len);
}
