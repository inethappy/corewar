/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 04:15:37 by vkryvono          #+#    #+#             */
/*   Updated: 2018/09/30 14:09:48 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

unsigned char	ft_flags(char **ptr, t_var *var)
{
	const char	*mask = " #0-+";

	while ((**ptr != '\0') && ft_strchr(mask, **ptr))
	{
		var->flags |= (**ptr == ' ') ? F_SPACE : 0;
		var->flags |= (**ptr == '#') ? F_ALTER : 0;
		var->flags |= (**ptr == '0') ? F_ZERO : 0;
		var->flags |= (**ptr == '-') ? F_LJUST : 0;
		var->flags |= (**ptr == '+') ? F_SIGN : 0;
		var->flags &= (**ptr == '+') ? ~F_SPACE : ~0;
		(*ptr)++;
	}
	return (var->flags);
}

int				ft_width(char **ptr, t_var *var)
{
	if (ft_isdigit(**ptr))
	{
		var->width = ft_atoi(*ptr);
		while (ft_isdigit(**ptr))
			(*ptr)++;
	}
	return (var->width);
}

int				ft_precision(char **ptr, t_var *var)
{
	if (ft_isdigit(**ptr))
	{
		var->prec = ft_atoi(*ptr);
		while (ft_isdigit(**ptr))
			(*ptr)++;
	}
	else
		var->prec = 0;
	return (var->prec);
}

unsigned char	ft_size(char **ptr, t_var *var)
{
	if (**ptr == 'h')
	{
		if (var->size == SHORT)
			var->size = SHSHORT;
		else if (var->size < SHORT)
			var->size = SHORT;
	}
	if (**ptr == 'l')
	{
		if (var->size == LONG)
			var->size = LONGLONG;
		else if (var->size < LONG)
			var->size = LONG;
	}
	else if (**ptr == 'j')
		var->size = (var->size < MAXT) ? MAXT : var->size;
	else if (**ptr == 'z')
		var->size = (var->size < SIZET) ? SIZET : var->size;
	else if (**ptr == 'L')
		var->size = (var->size < INT64) ? INT64 : var->size;
	else if (**ptr == 't')
		var->size = (var->size < PTRDIFF) ? PTRDIFF : var->size;
	if (ft_strchr("hlLtjz", **ptr))
		(*ptr)++;
	return (var->size);
}

unsigned char	ft_type(char **c, t_var *var)
{
	var->type = 0;
	if (**c == 'c')
		var->type = (var->size == LONG) ? WCHAR : CHAR;
	else if (**c == 'C')
		var->type = WCHAR;
	else if (**c == 's')
		var->type = (var->size == LONG) ? WSTR : CSTR;
	else if (**c == 'S')
		var->type = WSTR;
	else if ((**c == 'i') || (**c == 'd') || (**c == 'D'))
		var->type = INT;
	else if (ft_strchr("oOxXuU", **c))
		var->type = UINT;
	else if (**c == 'p')
		var->type = POINT;
	if (ft_strchr("DOU", **c))
		var->size = LONG;
	if ((**c == 'o') || (**c == 'O'))
		var->base = 8;
	else if ((**c == 'x') || (**c == 'X'))
		var->base = 16;
	var->type |= (**c == 'X') ? UPCASE : 0;
	*c += ((**c != '\0') && ft_strchr("cCsSidDoOuUxXp", **c)) ? 1 : 0;
	return (var->type);
}
