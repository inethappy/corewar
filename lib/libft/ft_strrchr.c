/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:53:31 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/09 13:57:09 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	t;
	size_t	i;

	t = (char)c;
	i = ft_strlen(s) + 1;
	while (s[--i] != t)
		if (s[i] == *s)
			return (NULL);
	return ((char *)(s + i));
}
