/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:55:43 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/13 13:55:47 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_one_word(const char *s, char c, int *i)
{
	int		j;
	char	*temp;

	j = 0;
	temp = (char *)malloc(sizeof(temp) * (ft_str_len_n(s, c)) + 1);
	while (s[*i] == c && s[*i] != '\0')
		*i += 1;
	while (s[*i] != c && s[*i])
	{
		temp[j] = s[*i];
		j++;
		*i += 1;
	}
	temp[j] = '\0';
	return (temp);
}
