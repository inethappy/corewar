/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 17:35:20 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 15:20:28 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (1);
	if (s1 && s2 && n)
	{
		if (ft_strncmp(s1, s2, n) > 0 || ft_strncmp(s1, s2, n) < 0)
			return (0);
		else
			return (1);
	}
	return (0);
}
