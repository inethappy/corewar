/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exception.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 07:10:51 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/13 07:10:53 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

size_t	ft_exception(char **buff, char **ptr, t_var *var)
{
	size_t	len;

	len = (size_t)((var->width > 0) ? (size_t)var->width : 0);
	len += ((len == 0) && (**ptr != '\0')) ? 1 : 0;
	*buff = ft_strnew(len);
	if (var->flags & F_LJUST)
		var->flags &= ~F_ZERO;
	if (var->flags & F_ZERO)
		ft_memset(*buff, '0', len);
	else
		ft_memset(*buff, ' ', len);
	if (**ptr != '\0')
	{
		if (var->flags & F_LJUST)
			(*buff)[0] = **ptr;
		else
			(*buff)[len - 1] = **ptr;
		(*ptr)++;
	}
	return (len);
}
