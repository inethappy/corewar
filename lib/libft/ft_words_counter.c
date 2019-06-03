/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_counter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:56:08 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/13 13:56:10 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_words_counter(const char *s, char c)
{
	int i;
	int word;

	if (!s || !c || *s == '\0')
		return (0);
	i = 0;
	word = 0;
	if (s[0] != c)
		word++;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			word++;
		i++;
	}
	return (word);
}
