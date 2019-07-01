/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:41:07 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/23 19:48:03 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;
	size_t	len1;
	size_t	len2;

	if (!(s1 || s2))
		return (NULL);
	len1 = (s1) ? ft_strlen(s1) : 0;
	len2 = (s2) ? ft_strlen(s2) : 0;
	concat = ft_strnew(len1 + len2);
	if (concat)
	{
		concat = (s1) ? ft_strncpy(concat, s1, len1) : concat;
		concat = (s2) ? ft_strncat(concat, s2, len2) : concat;
	}
	return (concat);
}
