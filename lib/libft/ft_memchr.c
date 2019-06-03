/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:33:53 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 17:51:52 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char *tmp;

	tmp = (const char *)s;
	while (n--)
	{
		if (*tmp++ == (char)c)
			return ((void *)tmp - 1);
	}
	return (NULL);
}
