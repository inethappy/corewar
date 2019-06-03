/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:54:52 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/09 14:02:08 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hs, const char *n)
{
	char	*hs_temp;
	char	*n_temp;
	size_t	i;

	hs_temp = (char *)hs;
	n_temp = (char *)n;
	i = ft_strlen(n_temp);
	if (i == 0)
		return (hs_temp);
	while (*hs_temp)
	{
		if (ft_strncmp(hs_temp, n_temp, i) == 0)
			return (hs_temp);
		hs_temp++;
	}
	return (NULL);
}
