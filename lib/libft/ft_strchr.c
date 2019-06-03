/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:52:30 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 15:17:51 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*t;
	unsigned int	i;

	i = 0;
	t = (char *)s;
	while (t[i] && t[i] != c)
		i++;
	if (t[i] == c)
		return (t + i);
	return (NULL);
}
