/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:31:00 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/02/28 18:31:41 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*join_all(char *s1, char *s2, char *s3)
{
	char	*fresh;
	int		i;
	int		a;
	int		b;
	int		c;

	fresh = NULL;
	a = (s1) ? ft_strlen(s1) : 0;
	b = (s2) ? ft_strlen(s2) : 0;
	c = (s3) ? ft_strlen(s3) : 0;
	if (!s1 && !s2 && !s3)
		return (NULL);
	i = a + b + c + 1;
	if (!(fresh = (char *)malloc(sizeof(char) * i)))
		return (NULL);
	(s1) ? ft_strcpy(fresh, s1) : 0;
	if (s2)
		(s1) ? ft_strcat(fresh, s2) : ft_strcpy(fresh, s2);
	if (s3)
		(s1 || s2) ? ft_strcat(fresh, s3) : ft_strcpy(fresh, s3);
	(s1) ? free(s1) : 0;
	(s2) ? free(s2) : 0;
	(s3) ? ft_strdel(&s3) : 0;
	return (fresh);
}

int		ft_null(t_b *base, t_flags *fl)
{
	char	*st;
	int		i;

	i = -1;
	st = ft_strdup("(null)\0");
	if (fl->prec)
	{
		base->str = ft_strnew(fl->prec + 1);
		while (++i < fl->prec)
			base->str[i] = st[i];
	}
	else
		base->str = ft_strdup(st);
	free(st);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

void	del_str(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

char	*put_sign(long long int di, t_flags *fl)
{
	char *sign;

	sign = ft_strnew(1);
	if (fl->plus && di >= 0)
		sign[0] = '+';
	else if (di < 0 || ((di < 0)
				&& (fl->width > fl->prec || fl->width < fl->prec)))
		sign[0] = '-';
	else if (fl->space && di >= 0 && (!fl->prec || fl->prec < fl->width))
		sign[0] = ' ';
	else if (fl->space && di >= 0 && !fl->plus
		&& (!fl->width || fl->width <= fl->prec || (di == 0 && fl->width)))
	{
		sign[0] = ' ';
		if (fl->width > fl->prec)
			fl->width--;
	}
	if (!sign)
	{
		free(sign);
		return (NULL);
	}
	return (sign);
}
