/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:39:48 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/23 19:41:17 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*buf;
	int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	buf = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	i = 0;
	if (buf)
	{
		while (s[i])
		{
			buf[i] = (*f)(s[i]);
			i++;
		}
		buf[i] = '\0';
	}
	return (buf);
}
