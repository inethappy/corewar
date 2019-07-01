/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 11:00:23 by vkryvono          #+#    #+#             */
/*   Updated: 2018/09/12 17:58:27 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf(const char *restrict_format, ...)
{
	va_list	args;
	int		len;

	va_start(args, restrict_format);
	len = ft_vprintf(restrict_format, args);
	va_end(args);
	return (len);
}

int	ft_dprintf(int fd, const char *restrict_format, ...)
{
	va_list	args;
	int		len;

	va_start(args, restrict_format);
	len = ft_vdprintf(fd, restrict_format, args);
	va_end(args);
	return (len);
}

int	ft_sprintf(char *str, const char *restrict_format, ...)
{
	va_list	args;
	int		len;

	va_start(args, restrict_format);
	len = ft_vsprintf(str, restrict_format, args);
	va_end(args);
	return (len);
}

int	ft_snprintf(char *str, size_t size, const char *restrict_format, ...)
{
	va_list	args;
	int		len;

	va_start(args, restrict_format);
	len = ft_vsnprintf(str, size, restrict_format, args);
	va_end(args);
	return (len);
}
