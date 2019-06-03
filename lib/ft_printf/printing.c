/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:20:47 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/03/01 14:20:49 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_con_scpf(t_b *base, t_flags *fl)
{
	long double f;

	if (fl->con == 'f' || fl->con == 'F')
	{
		f = (long double)va_arg(base->ap, double);
		ft_ftoa(f, base, fl);
		ft_putstr(base->str);
		return (ft_strlen(base->str));
	}
	if (fl->con == 's' || fl->con == 'S')
		return (ft_printing_s(base, fl));
	if (fl->con == 'c' || fl->con == 'C')
		return (ft_printing_c(base, fl));
	else
		return (ft_printing_p(base, fl));
	return (0);
}

int	print_con_di(t_b *base, t_flags *fl)
{
	long long int di;

	di = cast_di(base, fl);
	fl->space = fl->plus ? 0 : fl->space;
	base->str = (di < 0) ? ft_itoa_signed(-di) : ft_itoa_signed(di);
	fl->len = (di < 0) ? (ft_strlen(base->str) + 1) : (ft_strlen(base->str));
	base->sign = put_sign(di, fl);
	if (di == 0 && (fl->dot || fl->dot == -1))
	{
		base->str = NULL;
		fl->len = 0;
	}
	if (!fl->minus)
		put_dio_if_not_minus(di, fl, base);
	else
		put_dio_if_minus(di, fl, base);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

int	print_con_o(t_b *base, t_flags *fl)
{
	unsigned long long int o;

	o = cast_ou(base, fl);
	base->str = ft_itoa_base(o, 8, fl);
	fl->len = (ft_strlen(base->str));
	fl->space = 0;
	fl->plus = 0;
	base->sign = ((fl->width && fl->width > fl->len)
		&& (fl->space || fl->plus)) ? ft_strdup(" ") : NULL;
	if (fl->minus && base->sign)
	{
		ft_strdel(&base->sign);
		base->sign = ft_strnew(1);
		fl->width += (fl->width) ? 1 : 0;
	}
	if (o == 0 && (fl->dot || fl->dot == -1) && !fl->width && !fl->hash)
		return (0);
	if (fl->hash)
		check_flags_nb(fl, o);
	if (!fl->minus)
		put_dio_if_not_minus(o, fl, base);
	else
		put_dio_if_minus(o, fl, base);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

int	print_con_u(t_b *base, t_flags *fl)
{
	unsigned long long int u;

	u = cast_ou(base, fl);
	base->str = ft_itoa_unsigned(u);
	base->sign = NULL;
	fl->plus = 0;
	fl->space = 0;
	fl->len = (ft_strlen(base->str));
	if (u == 0 && fl->dot && !fl->width)
		return (0);
	if (!fl->minus)
		put_dio_if_not_minus(u, fl, base);
	else
		put_dio_if_minus(u, fl, base);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

int	print_con_x(t_b *base, t_flags *fl)
{
	unsigned long long int x;

	x = cast_ou(base, fl);
	base->str = ft_itoa_base(x, 16, fl);
	base->sign = NULL;
	fl->plus = 0;
	fl->space = 0;
	fl->len = (ft_strlen(base->str));
	if (x == 0 && fl->dot && !fl->width)
		return (0);
	if (fl->hash && fl->width && x != 0)
		fl->width -= 2;
	check_flags_nb(fl, x);
	if (x != 0 && fl->hash && (!fl->null || fl->minus) && !fl->prec)
		base->str = hash_x_func(fl, base->str, x);
	if (!fl->minus)
		put_dio_if_not_minus(x, fl, base);
	else
		put_dio_if_minus(x, fl, base);
	if (x != 0 && fl->hash && fl->prec && (!fl->null || fl->minus))
		base->str = hash_x_func(fl, base->str, x);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}
