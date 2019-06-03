/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 17:27:49 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/09 14:18:06 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *new;

	new = (char*)malloc(sizeof(char) * size + 1);
	if (new == NULL)
		return (NULL);
	ft_memset(new, 0, (size + 1));
	return (new);
}
