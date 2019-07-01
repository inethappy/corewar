/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 17:48:29 by vkryvono          #+#    #+#             */
/*   Updated: 2018/09/12 19:09:32 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_vprintf(const char *restrict_format, va_list ap)
{
	return (ft_vdprintf(1, restrict_format, ap));
}

int	ft_vdprintf(int fd, const char *restrict_format, va_list ap)
{
	int		len;
	char	*buff;
	char	*form;

	buff = NULL;
	form = (char *)restrict_format;
	len = ft_parse(&buff, form, ap);
	if (len > -1)
		write(fd, buff, (size_t)len);
	ft_memdel((void **)&buff);
	return (len);
}

int	ft_vsprintf(char *str, const char *restrict_format, va_list ap)
{
	int		len;
	char	*buff;
	char	*form;

	if (!str)
		return (0);
	buff = NULL;
	form = (char *)restrict_format;
	len = ft_parse(&buff, form, ap);
	if (len > -1)
		ft_memcpy(str, buff, (size_t)len);
	ft_memdel((void **)&buff);
	return (len);
}

int	ft_vsnprintf(char *str, size_t size,\
					const char *restrict_format, va_list ap)
{
	int		len;
	char	*buff;
	char	*form;

	if (!str)
		return (0);
	buff = NULL;
	form = (char *)restrict_format;
	len = ft_parse(&buff, form, ap);
	if (len > -1)
		ft_memcpy(str, buff, size);
	ft_memdel((void **)&buff);
	return (len);
}
