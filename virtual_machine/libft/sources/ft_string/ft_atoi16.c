/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi16.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 01:18:32 by vkryvono          #+#    #+#             */
/*   Updated: 2018/08/08 01:29:40 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi16(const char *str)
{
	char				*mask;
	int					i;
	unsigned long long	num;

	num = 0;
	i = 0;
	mask = ft_strdup("0123456789ABCDEF");
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	while (ft_strchr(mask, (int)str[i]))
	{
		num *= 16;
		num += (unsigned long long)(ft_strchr(mask, str[i]) - mask[0]);
		i++;
	}
	return ((int)num);
}
