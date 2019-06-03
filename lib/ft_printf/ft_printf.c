/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:23:20 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/02/28 18:23:26 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	con_not_found(t_b *base, t_flags *fl)
{
	char *ss;

	if (*base->fmt == '%')
	{
		if (fl->width > 1)
		{
			ss = ft_strnew(fl->width - 1);
			(fl->null && !fl->minus) ? ft_memset(ss, 48, (fl->width - 1))
				: ft_memset(ss, 32, fl->width - 1);
			base->str = fl->minus ? (ft_strjoin("%", ss))
				: (ft_strjoin(ss, "%"));
			free(ss);
		}
		else
			base->str = ft_strdup("%");
		ft_putstr(base->str);
		base->res = base->res + ft_strlen(base->str);
		base->fmt++;
	}
	else
		base->res = base->res + ft_printing_c(base, fl);
}

void	search_param(t_b *base, t_flags *fl)
{
	if (ft_strchr("#0- +", *base->fmt))
		ft_search_fl(base->fmt, fl);
	else if (ft_strchr("123456789*", *base->fmt))
		ft_search_width(base, fl);
	else if (ft_strchr(".", *base->fmt))
		ft_search_prec(base, fl);
	else if (ft_strchr("zhlLj", *base->fmt))
		ft_search_length(base->fmt, fl);
}

void	ft_parsing(t_b *base, t_flags *fl)
{
	while (*base->fmt != '\0')
	{
		if (ft_strchr(" 0+#-123456789*.lzhjL", *base->fmt))
			search_param(base, fl);
		else
			break ;
		base->fmt++;
	}
	if (*base->fmt == '\0')
		return ;
	if (ft_strchr("dDioOuUxXsScCpfF", *base->fmt))
	{
		fl->con = *base->fmt;
		base->fmt++;
		work_cur_case(base, fl);
	}
	else
		con_not_found(base, fl);
	base->str ? (ft_strdel(&base->str)) : 0;
}

int		ft_printf(const char *format, ...)
{
	t_b		base;
	t_flags	fl;

	ft_bzero(&fl, sizeof(fl));
	ft_bzero(&base, sizeof(base));
	base.fmt = (char *)format;
	va_start(base.ap, format);
	while (*base.fmt != '\0')
	{
		if (*base.fmt == '%')
		{
			base.fmt++;
			ft_parsing(&base, &fl);
		}
		if (*base.fmt && *base.fmt != '%')
		{
			ft_putchar(*base.fmt);
			base.res++;
			base.fmt++;
		}
	}
	va_end(base.ap);
	return (base.res);
}
