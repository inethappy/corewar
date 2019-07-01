/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 04:11:44 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/31 04:12:09 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void **memory, size_t old_size, size_t new_size)
{
	void	*newmemory;
	size_t	size;

	if ((newmemory = ft_memalloc(new_size)) == NULL)
		return (NULL);
	if (old_size < new_size)
		size = old_size;
	else
		size = new_size;
	ft_memcpy(newmemory, *memory, size);
	ft_memdel(memory);
	return (newmemory);
}
