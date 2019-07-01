/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 15:54:07 by vkryvono          #+#    #+#             */
/*   Updated: 2018/09/30 15:54:10 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static char		*ft_pointer(va_list ap, t_var *var)
{
	void	*ptr;
	char	*str;
	char	*buff;
	size_t	len;

	ptr = va_arg(ap, void *);
	if (ptr != NULL)
		str = ft_uitoabase((uintmax_t)ptr, 16);
	else
		str = (var->prec != 0) ? ft_strdup("0") : NULL;
	if (str == NULL)
		return (NULL);
	len = ft_strslen(str);
	len = (var->prec > (int)len) ? var->prec - len : 0;
	buff = ft_strnew(len);
	buff = ft_memset(buff, '0', len);
	buff = ft_strappend(&buff, &str);
	return (buff);
}

size_t			ft_ptrstr(char **buff, va_list ap, t_var *var)
{
	size_t	len;
	char	*str;
	char	*prefix;

	str = ft_pointer(ap, var);
	len = ft_strslen(str) + 2;
	len = (var->width > (int)len) ? var->width - len : 0;
	*buff = ft_strnew(len);
	prefix = ft_strdup("0x");
	if ((var->prec < 0) && (var->flags & F_ZERO) && !(var->flags & F_LJUST))
	{
		*buff = ft_memset(*buff, '0', len);
		*buff = ft_strappend(&prefix, buff);
		*buff = ft_strappend(buff, &str);
	}
	else if (!(var->flags & F_ZERO))
	{
		*buff = ft_memset(*buff, ' ', len);
		str = ft_strappend(&prefix, &str);
		*buff = (var->flags & F_LJUST) ? ft_strappend(&str, buff)
										: ft_strappend(buff, &str);
	}
	return (ft_strlen(*buff));
}
