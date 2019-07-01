/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 02:09:50 by vkryvono          #+#    #+#             */
/*   Updated: 2018/09/18 02:10:24 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str)
{
	char	*buff;
	int		i;

	if (!str)
		return (NULL);
	buff = ft_strnew(ft_strlen(str));
	i = 0;
	while (str[i])
	{
		buff[i] = (char)ft_tolower(str[i]);
		i++;
	}
	return (buff);
}
