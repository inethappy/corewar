/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filesize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 06:08:05 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/22 06:08:08 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/types.h>
#include <sys/stat.h>

size_t		ft_filesize(const char *path)
{
	struct stat		statbuf;

	if (stat(path, &statbuf) != 0)
		return ((size_t)(statbuf.st_size));
	return (0);
}
