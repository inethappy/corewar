/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 10:48:36 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/12/12 13:37:05 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check(char *storage)
{
	int i;

	i = 0;
	while (storage[i] && i < (BUFF_SIZE + 1))
	{
		if (storage[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int		write_storage(char **line, char **storage)
{
	int		i;
	char	*bufer;

	i = 0;
	if (!*storage)
		return (0);
	if ((i = check(*storage)) >= 0)
	{
		*line = ft_strnew(i);
		ft_memcpy(*line, *storage, i);
		bufer = *storage;
		*storage = ft_strdup(bufer + i + 1);
		ft_strdel(&bufer);
		return (1);
	}
	*line = ft_strdup(*storage);
	ft_strdel(storage);
	return (0);
}

static char		*join(char **line, char *tmp, int n)
{
	char	*bufer;
	int		i;

	i = 0;
	if (*line)
		i = ft_strlen(*line);
	bufer = ft_strnew(i + n);
	ft_memcpy(bufer, *line, i);
	ft_memcpy(bufer + i, tmp, n);
	ft_strdel(line);
	*line = ft_strdup(bufer);
	ft_strdel(&bufer);
	return (*line);
}

static int		split(char *tmp, char **storage, char **line, int res)
{
	int i;

	i = 0;
	while (i < res && tmp[i])
	{
		if (tmp[i] == '\n')
		{
			*line = join(line, tmp, i);
			*storage = ft_strnew(res - i);
			ft_memcpy(*storage, (tmp + i + 1), (res - i - 1));
			return (1);
		}
		i++;
	}
	*line = join(line, tmp, res);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int				res;
	char			tmp[BUFF_SIZE];
	char static		*storage[355];
	int				var;

	res = 0;
	var = 0;
	if (!line || BUFF_SIZE <= 0 || fd < 0 || (res = read(fd, tmp, 0)) < 0)
		return (-1);
	*line = NULL;
	if ((var = write_storage(line, &storage[fd])) == 1)
		return (1);
	while ((res = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		if ((var = split(tmp, &storage[fd], line, res) == 1))
			return (1);
	}
	if (*line && res == 0)
	{
		if (storage[fd])
			ft_strdel(&storage[fd]);
		if (ft_strlen(*line) > 0)
			return (1);
	}
	return (0);
}
