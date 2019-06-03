/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:42:09 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/03/08 16:42:12 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_flags_nb(t_flags *fl, unsigned long long int nb)
{
	if (fl->con == 'o' || fl->con == 'O')
	{
		if (nb != 0 && fl->len > 21 && ((!fl->width && fl->prec
			&& fl->prec <= fl->len) || (fl->prec && fl->prec <= fl->len)))
			fl->prec = fl->len;
		else if (nb != 0
			&& ((!fl->width && fl->prec && fl->prec <= fl->len)
			|| (fl->prec && fl->prec <= fl->len)))
			fl->prec = fl->len + 1;
		else if (nb == 0
			&& ((!fl->width && fl->prec && fl->prec <= fl->len)
			|| (fl->prec && fl->prec <= fl->len)))
			fl->prec = fl->len;
		else if (!fl->prec && nb != 0)
			fl->prec = fl->len + 1;
	}
	else
	{
		if ((fl->prec && fl->prec <= fl->len) || fl->dot == -1
			|| (!fl->prec && !fl->width && fl->null))
		{
			fl->null = 0;
			fl->prec = 0;
		}
	}
}

char	*hash_x_func(t_flags *fl, char *str, long long int x)
{
	char *buff;

	buff = NULL;
	if (fl->con == 'o' || fl->con == 'O')
		return (str);
	if (fl->con == 'x' || fl->con == 'p')
		buff = (x == 0 && fl->dot) ? ft_strdup("0x") : ft_strjoin("0x", str);
	else if (fl->con == 'X')
		buff = (x == 0 && fl->dot) ? ft_strdup("0X") : ft_strjoin("0X", str);
	free(str);
	return (buff);
}

int		ft_len_nb(long long int nb)
{
	int len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	else if (nb == 0)
		len = 1;
	while (nb > 0 && ++len)
		nb /= 10;
	return (len);
}

char	*f_after_dot(t_flags *fl, long double nb)
{
	char	*new;
	char	*buf;
	int		i;
	int		j;

	i = 0;
	while (i <= fl->prec)
		i++;
	if (nb < 0.1)
		j = -1;
	while (--i)
		nb *= 10;
	buf = ft_itoa_unsigned((unsigned long long int)nb);
	if (j == -1 && fl->prec != 1)
		new = ft_strjoin("0", buf);
	else
		new = ft_strdup(buf);
	free(buf);
	return (new);
}

void	params_dio_minus(t_flags *fl, long long int di, t_b *base)
{
	int		i;
	char	*s;

	i = fl->width;
	fl->width = 0;
	s = (fl->con == 'o' || fl->con == 'u' || fl->con == 'O' || fl->con == 'U'
		|| fl->con == 'x' || fl->con == 'X') ? paddings(di, fl, 48)
		: ft_strjoin(base->sign, paddings(di, fl, 48));
	s = ft_strjoin(s, base->str);
	fl->width = ((fl->plus || fl->space) && di > 0)
		? (i + ft_strlen(base->sign)) : i;
	fl->len = ft_strlen(s);
	fl->prec = 0;
	ft_strdel(&base->sign);
	base->str = join_all(base->sign, s, paddings(di, fl, 32));
}
