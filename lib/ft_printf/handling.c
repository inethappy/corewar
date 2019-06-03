/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:28:25 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/02/28 18:28:27 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa_base(unsigned long long int value, int base, t_flags *fl)
{
	char					*str;
	int						i;
	unsigned long long int	value_tmp;
	char					x;

	x = (fl->con == 'x' || fl->con == 'p') ? 'a' : 'A';
	value_tmp = value;
	i = 1;
	while ((value_tmp /= base) >= 1)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	value_tmp = value;
	while (i--)
	{
		str[i] = (value_tmp % base < 10) ?
			value_tmp % base + '0' : value_tmp % base + x - 10;
		value_tmp /= base;
	}
	return (str);
}

char		*ft_itoa_signed(long long int n)
{
	char	*fresh;
	int		len;

	len = ft_len_nb(n);
	if (!(fresh = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (n < -9223372036854775807)
		return (ft_strdup("9223372036854775808"));
	if (n == 0)
		fresh[0] = '0';
	fresh[len] = '\0';
	while (n > 0 && len > 0)
	{
		fresh[--len] = n % 10 + '0';
		n /= 10;
	}
	return (fresh);
}

char		*ft_itoa_unsigned(unsigned long long int n)
{
	char						*fresh;
	int							len;
	unsigned long long int		nb;

	len = 0;
	nb = n;
	if (nb == 0)
		len = 1;
	while (nb > 0 && ++len)
		nb /= 10;
	if (!(fresh = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (n == 0)
		fresh[0] = '0';
	fresh[len] = '\0';
	while (n > 0 && len > 0)
	{
		fresh[--len] = n % 10 + '0';
		n /= 10;
	}
	return (fresh);
}

ssize_t		cast_di(t_b *base, t_flags *fl)
{
	if (fl->z)
		return (va_arg(base->ap, size_t));
	else if (fl->j)
		return (va_arg(base->ap, intmax_t));
	else if (fl->ll || fl->con == 'D')
		return (va_arg(base->ap, long long int));
	else if (fl->l)
		return (va_arg(base->ap, long int));
	else if (fl->h)
		return ((short)va_arg(base->ap, int));
	else if (fl->hh)
		return ((signed char)va_arg(base->ap, int));
	else
		return (va_arg(base->ap, int));
}

size_t		cast_ou(t_b *base, t_flags *fl)
{
	if (fl->z)
		return (va_arg(base->ap, size_t));
	else if (fl->j)
		return (va_arg(base->ap, intmax_t));
	else if (fl->ll || fl->con == 'O' || fl->con == 'U')
		return (va_arg(base->ap, unsigned long long int));
	else if (fl->l)
		return (va_arg(base->ap, unsigned long int));
	else if (fl->h)
		return ((unsigned short)va_arg(base->ap, unsigned int));
	else if (fl->hh)
		return ((unsigned char)va_arg(base->ap, unsigned int));
	else
		return (va_arg(base->ap, unsigned int));
}
