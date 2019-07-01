/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:24:26 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/25 12:52:04 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	unsigned int	i;
	unsigned int	j;

	if (*little == '\0')
		return ((char*)big);
	while (*big != '\0')
	{
		i = 0;
		j = 0;
		while ((big[j] == little[i]) && (little[i] != '\0'))
		{
			i++;
			j++;
		}
		if (little[i] == '\0')
			return ((char*)big);
		big++;
	}
	return (0);
}
