/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 12:47:19 by vkryvono          #+#    #+#             */
/*   Updated: 2018/09/30 12:47:22 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static size_t	ft_chr(char **buff, char c)
{
	*buff = ft_strnew(1);
	(*buff)[0] = c;
	return (1);
}

static size_t	ft_charbuff(char **buff, va_list ap, t_var *var)
{
	size_t	bufflen;

	bufflen = 0;
	if (var->type == CHAR)
		bufflen = ft_chr(buff, (char)va_arg(ap, unsigned int));
	else if (var->type == WCHAR)
		bufflen = ft_wctomb(buff, (unsigned int)va_arg(ap, wchar_t));
	return (bufflen);
}

static size_t	ft_strbuff(char **buff, va_list ap, t_var *var)
{
	char	*str;
	size_t	len;

	if (var->type == CSTR)
	{
		str = va_arg(ap, char *);
		*buff = (str) ? ft_strdup(str) : NULL;
	}
	else if (var->type == WSTR)
		*buff = ft_widetostr(va_arg(ap, wchar_t *));
	if (*buff == NULL)
		*buff = ft_strdup("(null)");
	len = ft_strlen(*buff);
	if ((var->prec >= 0) && (var->prec < (int)len))
	{
		str = ft_strsub(*buff, 0, (size_t)var->prec);
		ft_strdel(buff);
		*buff = ft_widetrim(&str);
	}
	return (ft_strlen(*buff));
}

size_t			ft_chrstr(char **buff, va_list ap, t_var *var)
{
	size_t	len;
	size_t	bufflen;
	char	*str;

	bufflen = (var->type < CSTR) ? ft_charbuff(buff, ap, var)
									: ft_strbuff(buff, ap, var);
	var->width = (var->width < (int)bufflen) ? (int)bufflen : var->width;
	str = ft_strnew((size_t)var->width);
	len = (var->width > (int)bufflen) ? var->width - bufflen : 0;
	if (var->flags & F_LJUST)
	{
		ft_memset((str + bufflen), ' ', len);
		ft_memcpy(str, *buff, bufflen);
	}
	else
	{
		if (var->flags & F_ZERO)
			ft_memset(str, '0', len);
		else
			ft_memset(str, ' ', len);
		ft_memcpy((str + len), *buff, bufflen);
	}
	ft_strdel(buff);
	*buff = str;
	return ((size_t)var->width);
}
