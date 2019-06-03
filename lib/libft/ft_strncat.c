/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:49:42 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 15:46:22 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*p;
	size_t	i;

	if (n == 0)
		return (dest);
	i = 0;
	p = dest;
	while (*dest)
		dest++;
	while (src[i] && i != n)
		*dest++ = src[i++];
	*dest = '\0';
	return (p);
}
