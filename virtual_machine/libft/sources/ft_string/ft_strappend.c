/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 14:45:53 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/15 09:12:44 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strappend(char **s1, char **s2)
{
	char	*new;

	if (!*s2)
		return (*s1);
	if (!*s1)
		return (*s2);
	new = ft_strjoin(*s1, *s2);
	if (*s1)
		ft_strdel(s1);
	if (*s2)
		ft_strdel(s2);
	return (new);
}
