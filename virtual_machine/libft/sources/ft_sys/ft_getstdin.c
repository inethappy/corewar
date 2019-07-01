/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:07:52 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/24 20:07:55 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_getstdin(char **str)
{
	long	len;
	size_t	total;
	char	*tmp;
	char	buff[100 + 1];

	total = 0;
	*str = ft_strnew(0);
	ft_bzero(buff, 101);
	while ((len = read(STDIN_FILENO, buff, 100)) > 0)
	{
		tmp = ft_strjoin(*str, buff);
		ft_strdel(str);
		*str = tmp;
		total += len;
		ft_bzero(buff, 100);
	}
	ft_putstr(*str);
	return (total);
}
