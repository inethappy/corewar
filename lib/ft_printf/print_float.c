/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.C                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:53:48 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/02/28 18:53:49 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_f_naninf(t_b *base, t_flags *fl, long double nb)
{
	char *s;
	char *s_pr;
	char *ss;

	s_pr = NULL;
	s = NULL;
	ss = NULL;
	if (nb != nb && nb != 0)
		s = (fl->con == 'f') ? ft_strdup("nan") : ft_strdup("NAN");
	else if ((nb * 2 == nb) && nb != 0)
	{
		s = ft_strnew(3 + fl->plus);
		if (fl->con == 'f')
			s = fl->plus ? ft_strncpy((s), "+inf", 4) : ft_strncpy(s, "inf", 3);
		else
			s = fl->plus ? ft_strncpy((s), "+INF", 4) : ft_strncpy(s, "INF", 3);
	}
	if (fl->dot || (size_t)fl->width > ft_strlen(s))
		ft_prec_s(fl, base, s, ss);
	else
		base->str = ft_strdup(s);
	if (s)
		free(s);
}

long double	help_f(t_flags *fl, long double nb, long double d, t_b *base)
{
	int			k;
	long double	tmp;

	base->fresh = (fl->dot || fl->hash) ? ft_strnew(fl->hlp + 1)
		: ft_strnew(fl->hlp);
	k = 0;
	if (nb < 1)
		base->fresh = ft_strdup("0");
	while ((nb >= 1 && k < fl->hlp) && (tmp = nb) && (tmp /= d))
	{
		tmp = (long long int)tmp;
		base->fresh[k++] = (long long int)tmp % 10 + '0';
		tmp *= d;
		nb -= tmp;
		d /= 10;
	}
	return (nb);
}

void		ft_ftoa(long double nb, t_b *base, t_flags *fl)
{
	long double	tmp;
	long double	del;
	long double	j;

	if ((nb != nb && nb != 0) || (nb * 2 == nb && nb != 0))
	{
		ft_f_naninf(base, fl, nb);
		return ;
	}
	fl->hlp = -1;
	del = 1;
	base->sign = put_sign((long long int)nb, fl);
	nb = (nb < 0) ? -nb : nb;
	j = 5;
	fl->prec = fl->prec ? fl->prec : 6;
	while (++fl->hlp <= fl->prec)
		j /= 10;
	nb += ((long long int)(nb) % 2 == 0) ? 0 : j;
	tmp = nb;
	while (tmp > 10 && ++fl->hlp && (tmp /= 10))
		del *= 10;
	nb = help_f(fl, nb, del, base);
	base->str = ft_prec_f(base->fresh, base, fl, nb);
}

char		*ft_make_str_f(t_b *base, t_flags *fl, char *str, char *fresh)
{
	char *new;
	char *buf;

	buf = paddings(ft_atoi(fresh), fl, fl->pad);
	if (fl->width)
	{
		if (fl->minus)
			new = join_all(base->sign, str, buf);
		else
			new = (fl->null) ? join_all(base->sign, buf, str)
				: join_all(buf, base->sign, str);
	}
	else
	{
		new = ft_strjoin(base->sign, str);
		del_str(str, base->sign);
	}
	if (fl->dot && fl->hash)
		new[ft_strlen(new)] = '.';
	return (new);
}

char		*ft_prec_f(char *fresh, t_b *base, t_flags *fl, long double nb)
{
	char			*new;
	char			*buf;

	fl->len = ft_strlen(fresh);
	fl->pad = (fl->null && !fl->minus) ? (48) : (32);
	if (fl->dot)
		return (ft_make_str_f(base, fl, fresh, fresh));
	fresh[fl->len] = '.';
	if (nb == 0)
	{
		new = ft_strnew(fl->prec + 1);
		ft_memset(new, 48, fl->prec);
	}
	else
		new = f_after_dot(fl, nb);
	buf = ft_strjoin(fresh, new);
	fl->len = ft_strlen(buf);
	del_str(fresh, new);
	fl->prec = 0;
	return (ft_make_str_f(base, fl, buf, fresh));
}
