/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:07:16 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/24 20:07:21 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_join(void **old, size_t *oldlen, void *buff, size_t len)
{
	void *file;

	file = ft_realloc(old, *oldlen, *oldlen + len);
	*old = ft_memcpy(file + *oldlen, buff, len);
	*oldlen += len;
}

size_t			ft_getfile(char *path, char **file)
{
	int		fd;
	int		len;
	size_t	total;
	char	buff[100 + 1];

	total = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	*file = ft_memalloc(101);
	ft_bzero(buff, 101);
	while ((len = (int)read(fd, buff, 100)) > 0)
	{
		ft_join((void **)file, &total, buff, (size_t)len);
		ft_bzero(buff, 100);
	}
	return (total);
}
