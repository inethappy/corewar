/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:24:12 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/03/01 14:24:15 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_search_fl(char *fmt, t_flags *fl)
{
	fl->hash = (*fmt == '#') ? 1 : fl->hash;
	fl->space = (*fmt == ' ') ? 1 : fl->space;
	fl->null = (*fmt == '0') ? 1 : fl->null;
	fl->minus = (*fmt == '-') ? 1 : fl->minus;
	fl->plus = (*fmt == '+') ? 1 : fl->plus;
}

void	ft_search_length(char *fmt, t_flags *fl)
{
	fl->h = (*fmt == 'h' && *(fmt - 1) != 'h') ? 1 : 0;
	fl->hh = (*fmt == 'h' && *(fmt - 1) == 'h') ? 1 : 0;
	fl->l = (*fmt == 'l' && *(fmt - 1) != 'l') ? 1 : 0;
	fl->ll = (*fmt == 'l' && *(fmt - 1) == 'l') ? 1 : 0;
	fl->lbig = (*fmt == 'L') ? 1 : fl->lbig;
	fl->z = (*fmt == 'z') ? 1 : fl->z;
	fl->j = (*fmt == 'j') ? 1 : fl->j;
}

void	ft_search_width(t_b *base, t_flags *fl)
{
	if ((fl->width = ft_atoi(base->fmt)))
		while (ft_strchr("1234567890", *(base->fmt + 1)))
			base->fmt += 1;
	else
		fl->width = va_arg(base->ap, int);
	if (fl->width < 0)
	{
		fl->minus = 1;
		fl->width = -fl->width;
	}
}

void	ft_search_prec(t_b *base, t_flags *fl)
{
	base->fmt++;
	if (*base->fmt == '0')
		fl->dot = -1;
	else if ((fl->prec = ft_atoi(base->fmt)))
		while (ft_strchr("0123456789", *(base->fmt + 1)))
			base->fmt++;
	else if (ft_strchr("*", *(base->fmt)))
	{
		fl->prec = va_arg(base->ap, int);
		if (fl->prec == 0)
			fl->dot = 1;
		if (fl->prec < 0)
			fl->prec = 0;
	}
	else
	{
		fl->dot = 1;
		if (*base->fmt != '0')
			base->fmt--;
	}
}

void	work_cur_case(t_b *base, t_flags *fl)
{
	fl->hash = (fl->con == 'X' || fl->con == 'x' || fl->con == 'o'
		|| fl->con == 'O' || fl->con == 'f' || fl->con == 'F') ? fl->hash : 0;
	if (ft_strchr("sScCpfF", fl->con))
		base->res = base->res + print_con_scpf(base, fl);
	else if (ft_strchr("dDi", fl->con))
		base->res = base->res + print_con_di(base, fl);
	else if (ft_strchr("oO", fl->con))
		base->res = base->res + print_con_o(base, fl);
	else if (ft_strchr("uU", fl->con))
		base->res = base->res + print_con_u(base, fl);
	else if (ft_strchr("xX", fl->con))
		base->res = base->res + print_con_x(base, fl);
}
