/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:57:57 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 15:55:43 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *n, size_t len)
{
	char	*hs_temp;
	char	*n_temp;
	size_t	i;

	hs_temp = (char *)hs;
	n_temp = (char *)n;
	i = ft_strlen(n_temp);
	if (i == 0)
		return (hs_temp);
	while (*hs_temp && len-- >= i)
	{
		if (ft_strncmp(hs_temp, n_temp, i) == 0)
			return (hs_temp);
		hs_temp++;
	}
	return (NULL);
}
