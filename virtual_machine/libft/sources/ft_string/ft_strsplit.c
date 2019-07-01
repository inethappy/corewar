/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:41:37 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/25 13:23:47 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static void		ft_lines(char const **s, char c, char ***array)
{
	int	i;
	int	num_of_lines;

	i = 0;
	num_of_lines = 1;
	while ((**s == c) && **s)
		(*s)++;
	while ((*s)[i])
	{
		if ((*s)[i] == c)
		{
			while ((*s)[i] == c)
				i++;
			if ((*s)[i])
				num_of_lines++;
		}
		i++;
	}
	*array = (char**)malloc((num_of_lines + 1) * sizeof(char*));
}

static char		*ft_strcdup(char const *str, char c)
{
	char		*buf;
	size_t		i;
	size_t		len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	if (!(buf = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		buf[i] = str[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		i;

	if (s == NULL)
		return (NULL);
	ft_lines(&s, c, &array);
	if (array == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			array[i++] = ft_strcdup(s, c);
			while (*s != c && *s)
				s++;
		}
	}
	array[i] = NULL;
	return (array);
}
