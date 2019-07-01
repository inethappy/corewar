/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:38:11 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/25 12:39:11 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*p;
	size_t	i;

	p = malloc(size);
	if (p != NULL)
	{
		i = 0;
		while (i < size)
		{
			p[i] = 0;
			i++;
		}
	}
	return (p);
}
