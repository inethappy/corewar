/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 23:35:27 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/02 13:13:48 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include "libft.h"

# define F_ZERO		(unsigned char)(1 << 0)
# define F_LJUST	(unsigned char)(1 << 1)
# define F_SPACE	(unsigned char)(1 << 2)
# define F_SIGN		(unsigned char)(1 << 3)
# define F_ALTER	(unsigned char)(1 << 4)

# define INT		(unsigned char)(1 << 0)
# define UINT		(unsigned char)(1 << 1)
# define CHAR		(unsigned char)(1 << 2)
# define WCHAR		(unsigned char)(1 << 3)
# define CSTR		(unsigned char)(1 << 4)
# define WSTR		(unsigned char)(1 << 5)
# define POINT		(unsigned char)(1 << 6)
# define UPCASE		(unsigned char)(1 << 7)

# define SHSHORT	(unsigned char)(1 << 0)
# define SHORT		(unsigned char)(1 << 1)
# define LONG		(unsigned char)(1 << 2)
# define SIZET		(unsigned char)(1 << 3)
# define LONGLONG	(unsigned char)(1 << 4)
# define MAXT		(unsigned char)(1 << 5)
# define INT64		(unsigned char)(1 << 6)
# define PTRDIFF	(unsigned char)(1 << 7)

typedef struct		s_arg
{
	unsigned char	flags;
	int				width;
	int				prec;
	unsigned char	size;
	unsigned char	base;
	unsigned char	type;
}					t_var;

int					ft_printf(const char *restrict_format, ...);
int					ft_dprintf(int fd, const char *restrict_format, ...);
int					ft_sprintf(char *str, const char *restrict_format, ...);
int					ft_snprintf(char *str, size_t size,
											const char *restrict_format, ...);

int					ft_vprintf(const char *restrict_format, va_list ap);
int					ft_vdprintf(int fd,
									const char *restrict_format, va_list ap);
int					ft_vsprintf(char *str,
									const char *restrict_format, va_list ap);
int					ft_vsnprintf(char *str, size_t size,
									const char *restrict_format, va_list ap);

unsigned char		ft_flags(char **ptr, t_var *var);
int					ft_width(char **ptr, t_var *var);
int					ft_precision(char **ptr, t_var *var);
unsigned char		ft_size(char **ptr, t_var *var);
unsigned char		ft_type(char **ptr, t_var *var);

size_t				ft_chrstr(char **buff, va_list ap, t_var *var);
size_t				ft_numstr(char **buff, va_list ap, t_var *var);
size_t				ft_ptrstr(char **buff, va_list ap, t_var *var);
size_t				ft_exception(char **buff, char **ptr, t_var *var);

int					ft_parse(char **buff, char *restrict_format, va_list ap);

#endif
