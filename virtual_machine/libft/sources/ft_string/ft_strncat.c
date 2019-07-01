/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:23:42 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/23 19:10:44 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = len1;
	j = 0;
	while (i < (len1 + len2))
	{
		if (i < len1 + n)
			s1[i] = s2[j++];
		else
			s1[i] = '\0';
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
