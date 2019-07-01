/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:56:20 by vkryvono          #+#    #+#             */
/*   Updated: 2018/09/30 13:56:25 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static char		*ft_uinteger(va_list ap, t_var *var)
{
	char	*str;

	if (var->size == LONG)
		str = ft_uitoabase(va_arg(ap, unsigned long), var->base);
	else if (var->size == LONGLONG)
		str = ft_uitoabase(va_arg(ap, unsigned long long), var->base);
	else if (var->size == SHORT)
		str = ft_uitoabase((unsigned short)va_arg(ap, unsigned int), var->base);
	else if (var->size == SHSHORT)
		str = ft_uitoabase((unsigned char)va_arg(ap, unsigned int), var->base);
	else if ((var->size == MAXT) || (var->size == INT64))
		str = ft_uitoabase((uintmax_t)va_arg(ap, uintmax_t), var->base);
	else if (var->size == SIZET)
		str = ft_uitoabase(va_arg(ap, size_t), var->base);
	else if (var->size == PTRDIFF)
		str = ft_itoabase(va_arg(ap, ptrdiff_t), var->base);
	else
		str = ft_uitoabase(va_arg(ap, unsigned int), var->base);
	if ((ft_strlen(str) == 1) && (*str == '0') && (var->base == 16))
		var->flags &= ~F_ALTER;
	return (str);
}

static char		*ft_integer(va_list ap, t_var *var)
{
	char	*str;

	if (var->size == LONG)
		str = ft_itoabase(va_arg(ap, long), var->base);
	else if (var->size == LONGLONG)
		str = ft_itoabase(va_arg(ap, long long), var->base);
	else if (var->size == SHORT)
		str = ft_itoabase((short)va_arg(ap, int), var->base);
	else if (var->size == SHSHORT)
		str = ft_itoabase((char)va_arg(ap, int), var->base);
	else if ((var->size == MAXT) || (var->size == INT64))
		str = ft_itoabase((intmax_t)va_arg(ap, intmax_t), var->base);
	else if (var->size == SIZET)
		str = ft_itoabase((size_t)va_arg(ap, intmax_t), var->base);
	else if (var->size == PTRDIFF)
		str = ft_itoabase((ptrdiff_t)va_arg(ap, intmax_t), var->base);
	else
		str = ft_itoabase(va_arg(ap, int), var->base);
	if ((ft_strlen(str) == 1) && (*str == '0') && (var->base == 16))
		var->flags &= ~F_ALTER;
	return (str);
}

static size_t	ft_prefix(char **buff, char sign, t_var *var)
{
	char	tmp[3];

	ft_bzero(tmp, 3);
	if ((var->base == 10) && (sign == '-'))
		ft_strcpy(tmp, "-");
	else if ((var->base == 10) && (var->flags & F_SIGN))
		ft_strcpy(tmp, "+");
	else if ((var->base == 10) && (var->flags & F_SPACE))
		ft_strcpy(tmp, " ");
	else if (var->flags & F_ALTER)
	{
		if (var->base == 8)
			ft_strcpy(tmp, "0");
		else if (var->base == 16)
			ft_strcpy(tmp, "0x");
	}
	else
	{
		*buff = NULL;
		return (0);
	}
	*buff = ft_strdup(tmp);
	return (ft_strlen(*buff));
}

static size_t	ft_number(char **str, t_var *var)
{
	char	*buff;
	char	*res;
	size_t	gaplen;
	size_t	len;

	if ((ft_strlen(*str) == 1) && (**str == '0') && (var->prec == 0))
		ft_strclr(*str);
	buff = ((*str)[0] == '-') ? (*str) + 1 : (*str);
	if ((var->base == 8) && (var->flags & F_ALTER) && (*buff == '0'))
		buff++;
	len = ft_strslen(buff);
	gaplen = (var->prec > (int)len) ? var->prec - len : 0;
	if ((var->base == 8) && (var->flags & F_ALTER) && (gaplen > 0))
		gaplen--;
	res = ft_strnew(gaplen + len);
	res = ft_memset(res, '0', gaplen);
	res = ft_strcat(res, buff);
	ft_strdel(str);
	*str = res;
	return (ft_strlen(*str));
}

size_t			ft_numstr(char **buff, va_list ap, t_var *var)
{
	size_t	len;
	char	*num;
	char	*prefix;

	prefix = NULL;
	var->flags &= (var->prec > -1) ? ~(F_ZERO) : 0xff;
	num = (var->type & UINT) ? ft_uinteger(ap, var) : ft_integer(ap, var);
	len = ft_prefix(&prefix, num[0], var) + ft_number(&num, var);
	len = (var->width > (int)(len)) ? (size_t)var->width - len : 0;
	*buff = ft_strnew(len);
	if ((var->prec < 0) && (var->flags & F_ZERO) && !(var->flags & F_LJUST))
	{
		*buff = ft_memset(*buff, '0', len);
		*buff = ft_strappend(&prefix, buff);
		*buff = ft_strappend(buff, &num);
	}
	else
	{
		*buff = ft_memset(*buff, ' ', len);
		num = ft_strappend(&prefix, &num);
		*buff = (var->flags & F_LJUST) ? ft_strappend(&num, buff)
										: ft_strappend(buff, &num);
	}
	return (ft_strlen(*buff));
}
