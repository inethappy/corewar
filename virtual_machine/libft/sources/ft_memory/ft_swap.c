/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 06:16:43 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/25 06:16:46 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned short		ft_swap16(unsigned short val)
{
	unsigned short	result;

	result = (unsigned short)((val & 0x00FF) << 8);
	result |= (unsigned short)((val & 0xFF00) >> 8);
	return (result);
}

unsigned int		ft_swap32(unsigned int val)
{
	unsigned int	result;

	result = (val & 0x000000FF) << 24;
	result |= (val & 0x0000FF00) << 8;
	result |= (val & 0x00FF0000) >> 8;
	result |= (val & 0xFF000000) >> 24;
	return (result);
}

unsigned long long	ft_swap64(unsigned long long val)
{
	unsigned long long	result;

	result = ((val) & 0x00000000000000FF) << 56;
	result |= ((val) & 0x000000000000FF00) << 40;
	result |= ((val) & 0x0000000000FF0000) << 24;
	result |= ((val) & 0x00000000FF000000) << 8;
	result |= ((val) & 0x000000FF00000000) >> 8;
	result |= ((val) & 0x0000FF0000000000) >> 24;
	result |= ((val) & 0x00FF000000000000) >> 40;
	result |= ((val) & 0xFF00000000000000) >> 56;
	return (result);
}
