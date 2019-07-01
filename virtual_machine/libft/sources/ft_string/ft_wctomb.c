/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 01:22:07 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/16 06:05:42 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_bytesize(int num)
{
	int len;

	len = 1;
	while ((num / 2) > 0)
	{
		num /= 2;
		len++;
	}
	if (len <= 7)
		return (1);
	if (len <= 11)
		return (2);
	if (len <= 16)
		return (3);
	return (4);
}

size_t			ft_wctomb(char **buff, unsigned int c)
{
	if ((*buff = ft_strnew(sizeof(c))) == NULL)
		return (0);
	if (ft_bytesize(c) == 1)
		(*buff)[0] = (char)(c | MASK_1);
	else if (ft_bytesize(c) == 2)
	{
		(*buff)[1] = (char)(((c << 26) >> 26) | ((MASK_2 << 24) >> 24));
		(*buff)[0] = (char)((((c >> 6) << 27) >> 27) | (MASK_2 >> 8));
	}
	else if (ft_bytesize(c) == 3)
	{
		(*buff)[2] = (char)(((c << 26) >> 26) | ((MASK_3 << 24) >> 24));
		(*buff)[1] = (char)((((c >> 6) << 26) >> 26) | ((MASK_3 << 16) >> 24));
		(*buff)[0] = (char)((((c >> 12) << 28) >> 28) | (MASK_3 >> 16));
	}
	else
	{
		(*buff)[3] = (char)(((c << 26) >> 26) | ((MASK_4 << 24) >> 24));
		(*buff)[2] = (char)((((c >> 6) << 26) >> 26) | ((MASK_4 << 16) >> 24));
		(*buff)[1] = (char)((((c >> 12) << 26) >> 26) | ((MASK_4 << 8) >> 24));
		(*buff)[0] = (char)((((c >> 18) << 29) >> 29) | (MASK_4 >> 24));
	}
	return (ft_bytesize(c));
}

char			*ft_widetostr(wchar_t *wstr)
{
	char	*buff;
	char	*symb;
	size_t	i;

	if (wstr == NULL)
		return (0);
	buff = ft_strnew(0);
	i = 0;
	while (wstr[i] != '\0')
	{
		ft_wctomb(&symb, (unsigned int)wstr[i]);
		buff = ft_strappend(&buff, &symb);
		i++;
	}
	return (buff);
}

char			*ft_widetrim(char **buff)
{
	size_t	i;
	size_t	size;
	size_t	len;
	char	*str;

	str = *buff;
	while (*str && ((*str & 0xff) >> 6) == 0b10)
		str++;
	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		size = (((str[i] & 0xff) >> 7) == (MASK_1 >> 7)) ? 1 : 0;
		size = (((str[i] & 0xff) >> 5) == (MASK_2 >> 13)) ? 2 : size;
		size = (((str[i] & 0xff) >> 4) == (MASK_3 >> 20)) ? 3 : size;
		size = (((str[i] & 0xff) >> 3) == (MASK_4 >> 27)) ? 4 : size;
		if (i + size > len)
		{
			str = ft_strsub(str, 0, i);
			ft_strdel(buff);
			return (str);
		}
		i += size;
	}
	return (*buff);
}
