/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:36:46 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 15:17:36 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char *s;
	char *a;

	if (!(s = (char*)malloc(sizeof(*s) * ft_strlen(src) + 1)))
		return (0);
	a = s;
	while (*src != '\0')
		*(a++) = *(src++);
	*a = '\0';
	return (s);
}
