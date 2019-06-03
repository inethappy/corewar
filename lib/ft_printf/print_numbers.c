/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:43:42 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/03/01 13:43:47 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_prec(long long int di, t_flags *fl, char *str)
{
	int i;
	int j;

	j = (di < 0) ? (fl->prec - fl->len + 1) : (fl->prec - fl->len);
	ft_memset((str + (fl->width - fl->prec)), 48, j);
	i = 0;
	while (str[i] && str[i + 1] != '0')
		i++;
	if (fl->plus && di >= 0 && fl->width > fl->prec
		&& fl->con != 'o' && fl->con != 'O')
		str[i] = '+';
	if (di < 0 && (fl->width > fl->prec))
		str[i] = '-';
}

int		padd_verify(t_flags *fl, long long int di)
{
	int wd;
	int var;

	var = 0;
	if (fl->width >= fl->prec)
	{
		wd = fl->width;
		wd -= ((fl->space || fl->plus) && fl->width && di >= 0) ? 1 : 0;
	}
	else
		wd = (di < 0) ? fl->prec + 1 : fl->prec;
	if (wd > fl->len)
		var = (wd - fl->len);
	return (var);
}

char	*paddings(long long int di, t_flags *fl, int pad)
{
	int		var;
	char	*str;

	var = 0;
	str = NULL;
	if ((fl->width > fl->prec && fl->width <= fl->len)
		|| (!fl->width && fl->prec < fl->len))
		return (NULL);
	var = padd_verify(fl, di);
	str = ft_strnew(var + 1);
	ft_memset(str, pad, var);
	if (fl->prec >= fl->len && fl->width > fl->len)
		put_prec(di, fl, str);
	else if (fl->prec < fl->len && fl->width > fl->len)
		if (fl->space && fl->null && (!fl->plus && di > 0))
			str[0] = 32;
	if (fl->hash && fl->null)
		str = ((fl->con == 'x' || fl->con == 'X') && di == 0) ? str
		: hash_x_func(fl, str, (long long int)di);
	return (str);
}

void	put_dio_if_not_minus(long long int di, t_flags *fl, t_b *base)
{
	if (!fl->width && !fl->prec && !fl->null)
		base->str = join_all(base->sign, paddings(di, fl, 48), base->str);
	else if ((fl->null && fl->width && !fl->prec && !fl->dot)
		|| (fl->width <= fl->prec) || (fl->prec && !fl->width))
		base->str = join_all(base->sign, paddings(di, fl, 48), base->str);
	else if (((!fl->null && ((fl->width && !fl->prec)
		|| (fl->width > fl->prec)))
		|| (fl->null && (fl->prec || fl->dot) && fl->width > fl->prec)))
	{
		if (base->str && di == 0 && fl->dot && fl->width)
			base->str[0] = 32;
		if (fl->width > fl->prec && fl->prec >= fl->len)
			ft_strdel(&base->sign);
		base->str = join_all(paddings(di, fl, 32), base->sign, base->str);
	}
}

void	put_dio_if_minus(long long int di, t_flags *fl, t_b *base)
{
	fl->null = 0;
	if (!fl->width && !fl->prec && !fl->null)
		base->str = join_all(base->sign, base->str, paddings(di, fl, 32));
	else if ((fl->width && !fl->prec) || fl->width > fl->prec)
	{
		if (fl->width > fl->prec && fl->width > fl->len && fl->prec >= fl->len)
			params_dio_minus(fl, di, base);
		else
			base->str = join_all(base->sign, base->str, paddings(di, fl, 32));
	}
	else if ((fl->prec && !fl->width) || (fl->prec >= fl->width))
		base->str = join_all(base->sign, paddings(di, fl, 48), base->str);
}
