/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 13:31:19 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/25 12:40:13 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)s1)[i] = ((unsigned char*)s2)[i];
		if (((unsigned char*)s2)[i] == (unsigned char)c)
			return ((s1 + i) + 1);
		i++;
	}
	return (NULL);
}
