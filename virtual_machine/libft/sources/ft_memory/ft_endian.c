/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 06:16:26 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/25 06:16:28 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_endian(void)
{
	int	num;

	num = 1;
	return (*(char *)&num == 1);
}

uintmax_t	ft_htob(uintmax_t host, size_t size)
{
	if (ft_endian() && (size > 1))
	{
		if (size == 2)
			host = ft_swap16((unsigned short)host);
		else if (size == 4)
			host = ft_swap32((unsigned int)host);
		else if (size == 8)
			host = ft_swap64((unsigned long long)host);
	}
	return (host);
}

uintmax_t	ft_btoh(uintmax_t host, size_t size)
{
	if (ft_endian() && (size > 1))
	{
		if (size == 2)
			host = ft_swap16((unsigned short)host);
		else if (size == 4)
			host = ft_swap32((unsigned int)host);
		else if (size == 8)
			host = ft_swap64((unsigned long long)host);
	}
	return (host);
}

uintmax_t	ft_htol(uintmax_t host, size_t size)
{
	if (!ft_endian() && (size > 1))
	{
		if (size == 2)
			host = ft_swap16((unsigned short)host);
		else if (size == 4)
			host = ft_swap32((unsigned int)host);
		else if (size == 8)
			host = ft_swap64((unsigned long long)host);
	}
	return (host);
}

uintmax_t	ft_ltoh(uintmax_t host, size_t size)
{
	if (!ft_endian() && (size > 1))
	{
		if (size == 2)
			host = ft_swap16((unsigned short)host);
		else if (size == 4)
			host = ft_swap32((unsigned int)host);
		else if (size == 8)
			host = ft_swap64((unsigned long long)host);
	}
	return (host);
}
