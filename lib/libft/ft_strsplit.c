/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 17:40:58 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 17:19:44 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**fresh;
	int		i;
	int		j;
	int		wd;

	if (!s || !c)
		return (NULL);
	wd = ft_words_counter(s, c);
	if (!(fresh = (char **)malloc(sizeof(char*) * wd + 1)))
		return (NULL);
	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	j = 0;
	while (s[i] != '\0' && j < wd)
	{
		fresh[j] = ft_one_word(s, c, &i);
		j++;
	}
	fresh[j] = NULL;
	return (fresh);
}
