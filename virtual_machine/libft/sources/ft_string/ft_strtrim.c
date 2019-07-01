/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:41:25 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/23 19:55:35 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*start;
	char	*end;
	char	*buf;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	start = (char*)s;
	while ((*start == ' ') || (*start == '\t') || (*start == '\n')
			|| (*start == ',' && *(start + 1) == ' '))
		start++;
	end = start;
	while (*(end + 1) != '\0')
		end++;
	while (((*end == ' ') || (*end == '\t') || (*end == '\n')
			|| (*end == ',' && *(end + 1) == ' ')) && end > start)
		end--;
	if ((buf = (char*)malloc((end - start + 2) * sizeof(char))) == NULL)
		return (NULL);
	while (start <= end)
		buf[i++] = *(start++);
	buf[i] = '\0';
	return (buf);
}
