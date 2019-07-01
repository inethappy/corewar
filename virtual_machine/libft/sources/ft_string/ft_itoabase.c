/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 00:10:03 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/15 10:52:52 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_discharge(uintmax_t num, int base)
{
	size_t	i;

	i = 1;
	while (num / base > 0)
	{
		num /= base;
		i++;
	}
	return (i);
}

char			*ft_uitoabase(uintmax_t num, int base)
{
	const char	*mask;
	char		*str;
	int			len;

	mask = "0123456789abcdef";
	len = (int)ft_discharge(num, base);
	if ((str = ft_strnew((size_t)len)) == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len--] = mask[num % base];
		num /= base;
	}
	return (str);
}

char			*ft_itoabase(intmax_t num, int base)
{
	char		*str;
	char		*buff;
	uintmax_t	abs;

	if (num < 0)
		str = ft_strdup("-");
	else
		str = NULL;
	abs = (uintmax_t)((num < 0) ? -num : num);
	buff = ft_uitoabase(abs, base);
	if (str)
		str = ft_strappend(&str, &buff);
	else
		str = buff;
	return (str);
}
