/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:44:32 by vkryvono          #+#    #+#             */
/*   Updated: 2018/09/15 22:48:33 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static t_var	*ft_varnew(void)
{
	t_var	*var;

	if ((var = (t_var *)ft_memalloc(sizeof(t_var))) == NULL)
		return (NULL);
	var->size = 0;
	var->width = -1;
	var->prec = -1;
	var->base = 10;
	var->flags = 0;
	var->type = 0;
	return (var);
}

static t_var	*ft_varinit(char **ptr)
{
	t_var	*var;

	if ((var = ft_varnew()) == NULL)
		return (NULL);
	while (**ptr != '\0')
	{
		if (ft_strchr(" #0-+", **ptr))
			var->flags = ft_flags(ptr, var);
		else if (ft_isdigit(**ptr))
			var->width = ft_width(ptr, var);
		else if (**ptr == '.')
		{
			(*ptr)++;
			var->prec = ft_precision(ptr, var);
		}
		else if (ft_strchr("hlLtjz", **ptr))
			var->size = ft_size(ptr, var);
		else
			break ;
	}
	var->type = (unsigned char)((**ptr != '\0') ? ft_type(ptr, var) : 0);
	return (var);
}

static int		ft_variable(char **buff, va_list ap, char **ptr)
{
	int		bufflen;
	t_var	*var;

	if ((var = ft_varinit(ptr)) == NULL)
		return (0);
	bufflen = 0;
	*buff = NULL;
	if (var->type & (UINT | INT))
	{
		var->flags &= (var->type == UINT) ? ~(F_SIGN | F_SPACE) : 0xff;
		bufflen = (int)ft_numstr(buff, ap, var);
		if (var->type & UPCASE)
			ft_strtoupper(*buff);
	}
	else if (var->type & (CHAR | WCHAR | CSTR | WSTR))
		bufflen = (int)ft_chrstr(buff, ap, var);
	else if (var->type == POINT)
	{
		var->size = 0;
		bufflen = (int)ft_ptrstr(buff, ap, var);
	}
	else if (var->type == 0)
		bufflen = (int)ft_exception(buff, ptr, var);
	ft_memdel((void **)&var);
	return (bufflen);
}

static int		ft_varjoin(char **buff, int bufflen, char **var, int varlen)
{
	int		len;
	char	*tmp;

	if (!(*var))
		return (bufflen);
	len = bufflen + varlen;
	tmp = ft_strnew((size_t)len);
	tmp = ft_memcpy(tmp, *buff, (size_t)bufflen);
	ft_strdel(buff);
	*buff = tmp;
	tmp += bufflen;
	ft_memcpy(tmp, *var, (size_t)varlen);
	ft_strdel(var);
	return (len);
}

int				ft_parse(char **buff, char *format, va_list ap)
{
	char	*ptr;
	char	*str;
	int		bufflen;
	int		varlen;
	size_t	offset;

	bufflen = 0;
	while (*format)
	{
		if ((ptr = ft_strchr(format, '%')) != NULL)
			offset = (ptr++) - format;
		else
			offset = ft_strslen(format);
		str = (offset > 0) ? ft_strsub(format, 0, offset) : NULL;
		bufflen = ft_varjoin(buff, bufflen, &str, (int)offset);
		if (ptr == NULL)
			return (bufflen);
		varlen = ft_variable(&str, ap, &ptr);
		bufflen = ft_varjoin(buff, bufflen, &str, varlen);
		format = ptr;
	}
	return (bufflen);
}
