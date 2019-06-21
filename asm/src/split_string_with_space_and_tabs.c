/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string_with_space_and_tabs.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:51:17 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/06/21 16:51:19 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

int		ft_words_counter_new(const char *s)
{
	int i;
	int word;

	if (!s || *s == '\0')
		return (0);
	i = 1;
	word = 0;
	if (s[0] != ' ' && s[0] != '\t')
		word++;
	while (s[i] != '\0')
	{
		if ((s[i] != ' ' && s[i] != '\t')
			&& (s[i - 1] == ' ' || s[i - 1] == '\t'))
			word++;
		i++;
	}
	return (word);
}

char	*ft_one_word_new(const char *s, int *i)
{
	int		j;
	char	*temp;
	char	c;

	j = 0;
	while (s[j] != ' ' && s[j] != '\t' && s[j] != '\0')
		j++;
	c = s[j];
	j = 0;
	temp = (char *)malloc(sizeof(temp) * (ft_str_len_n(s, c)) + 1);
	while ((s[*i] == ' ' || s[*i] == '\t') && s[*i] != '\0')
		*i += 1;
	while (s[*i] != ' ' && s[*i] != '\t' && s[*i])
	{
		temp[j] = s[*i];
		j++;
		*i += 1;
	}
	temp[j] = '\0';
	return (temp);
}

char	**ft_strsplit_new(char const *s)
{
	char	**fresh;
	int		i;
	int		j;
	int		wd;

	if (!s)
		return (NULL);
	wd = ft_words_counter_new(s);
	if (!(fresh = (char **)malloc(sizeof(char*) * wd + 1)))
		return (NULL);
	i = 0;
	while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
		i++;
	j = 0;
	while (s[i] != '\0' && j < wd)
	{
		fresh[j] = ft_one_word_new(s, &i);
		j++;
	}
	fresh[j] = NULL;
	return (fresh);
}
