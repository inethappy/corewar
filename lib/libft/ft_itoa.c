/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 17:44:47 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 17:20:07 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*fresh;
	int		len;

	len = ft_len_numb(n);
	if (!(fresh = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		fresh[0] = '0';
	else if (n < 0)
	{
		fresh[0] = '-';
		n = -n;
	}
	fresh[len] = '\0';
	while (n > 0 && len > 0)
	{
		fresh[--len] = n % 10 + '0';
		n /= 10;
	}
	return (fresh);
}
