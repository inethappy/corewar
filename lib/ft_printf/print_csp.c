/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:32:10 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/02/28 18:43:46 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printing_c(t_b *base, t_flags *fl)
{
	char c;

	fl->width = (fl->width == 0) ? 1 : fl->width;
	if (ft_strchr("dDioOuUxXsScCpfF", *(base->fmt - 1)))
		c = va_arg(base->ap, int);
	else
	{
		c = (*base->fmt);
		base->fmt++;
	}
	base->str = (ft_strnew(fl->width + fl->space + 1));
	if (c == 0)
	{
		(fl->null && !fl->minus) ? ft_memset(base->str, 48, (fl->width - 1))
			: ft_memset(base->str, 32, (fl->width - 1));
		fl->minus ? ft_putchar('\0') : ft_putstr(base->str);
		fl->minus ? ft_putstr(base->str) : ft_putchar('\0');
		return (ft_strlen(base->str) + 1);
	}
	(fl->null && !fl->minus) ? ft_memset(base->str, 48, fl->width)
		: ft_memset(base->str, 32, fl->width);
	fl->pad = fl->minus ? 0 : (fl->width - 1);
	base->str[fl->pad] = c;
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

void	ft_prec_s(t_flags *fl, t_b *base, char *s, char *ss)
{
	int i;

	i = (fl->dot) ? (fl->width) : (fl->width - ft_strlen(s));
	ss = ft_strnew(i);
	(fl->null && !fl->minus) ? ft_memset(ss, 48, i) : ft_memset(ss, 32, i);
	if (fl->dot)
		base->str = ft_strdup(ss);
	else
		base->str = fl->minus ? (ft_strjoin(s, ss)) : (ft_strjoin(ss, s));
	free(ss);
}

int		ft_printing_s(t_b *base, t_flags *fl)
{
	char *s;
	char *ss;
	char *s_pr;

	s_pr = NULL;
	s = NULL;
	ss = NULL;
	s = va_arg(base->ap, char*);
	if (((s == NULL && !fl->width) || (s == NULL && !fl->prec)) && !fl->dot)
		return (ft_null(base, fl));
	else if (s == NULL && fl->width)
		s = ft_strdup("0");
	if (fl->prec)
	{
		s_pr = ft_strnew(fl->prec);
		s_pr = ft_strncpy(s_pr, s, fl->prec);
		s = ft_strdup(s_pr);
		free(s_pr);
	}
	if (fl->dot || fl->width > (int)ft_strlen(s))
		ft_prec_s(fl, base, s, ss);
	else
		base->str = ft_strdup(s);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

void	ft_point_prec(t_flags *fl, t_b *base, long long x)
{
	int i;

	i = fl->width;
	fl->width = fl->prec;
	fl->prec = 0;
	base->str = (x != 0 && fl->width)
		? join_all(base->sign, paddings((int)x, fl, 48), base->str)
		: join_all(base->sign, paddings((int)x, fl, 48), base->str);
	fl->width = i;
	fl->len = (ft_strlen(base->str));
}

int		ft_printing_p(t_b *base, t_flags *fl)
{
	char	*x;

	x = va_arg(base->ap, void *);
	fl->hash = 1;
	base->sign = NULL;
	fl->space = 0;
	fl->plus = 0;
	base->str = ft_itoa_base((unsigned long long)x, 16, fl);
	fl->len = (ft_strlen(base->str));
	if (fl->hash && fl->width)
		fl->width -= 2;
	if (fl->prec)
		ft_point_prec(fl, base, (long long)x);
	if (fl->hash && (!fl->null || fl->minus) && !fl->prec)
		base->str = hash_x_func(fl, base->str, (long long int)x);
	if (!fl->minus)
		put_dio_if_not_minus((long long int)x, fl, base);
	else
		put_dio_if_minus((long long int)x, fl, base);
	if (x != 0 && fl->hash && fl->prec && (!fl->null || fl->minus))
		base->str = hash_x_func(fl, base->str, (long long int)x);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}
