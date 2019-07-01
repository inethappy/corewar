/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:25:44 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/25 12:08:55 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					flag;
	unsigned long long	num;

	num = 0;
	flag = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
		flag = ',' - str[i++];
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = 10 * num + ((int)str[i++] - '0');
		if ((num >= LL_MAX && flag == 1) || (num > LL_MAX && flag == -1))
			return (flag == -1 ? 0 : -1);
	}
	return ((int)num * flag);
}
