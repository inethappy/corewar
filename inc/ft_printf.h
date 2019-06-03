/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:47:44 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/03/08 17:47:47 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>

typedef struct	s_base
{
	va_list	ap;
	char	*fmt;

	char	*str;
	char	*sign;
	int		res;
	char	*fresh;
}				t_b;

typedef struct	s_flags
{
	int		len;

	int		hash;
	int		null;
	int		minus;
	int		space;
	int		plus;

	int		dot;

	int		width;

	int		prec;

	int		h;
	int		hh;
	int		l;
	int		ll;
	int		lbig;
	int		z;
	int		j;

	char	con;
	int		pad;
	int		hlp;
}				t_flags;

int				ft_printf(const char *format, ...);
void			ft_parsing(t_b *base, t_flags *fl);
void			con_not_found(t_b *base, t_flags *fl);
void			search_param(t_b *base, t_flags *fl);

void			ft_search_fl(char *fmt, t_flags *fl);
void			ft_search_prec(t_b *base, t_flags *fl);
void			ft_search_width(t_b *base, t_flags *fl);
void			ft_search_length(char *fmt, t_flags *fl);
void			ft_search_specifier(char *fmt, t_flags *fl);

void			work_cur_case(t_b *base, t_flags *fl);

int				print_con_scpf(t_b *base, t_flags *fl);
int				print_con_o(t_b *base, t_flags *fl);
int				print_con_di(t_b *base, t_flags *fl);
int				print_con_u(t_b *base, t_flags *fl);
int				print_con_x(t_b *base, t_flags *fl);

char			*paddings(long long int di, t_flags *fl, int pad);
char			*put_sign(long long int di, t_flags *fl);
void			put_dio_if_minus(long long int di, t_flags *fl, t_b *base);
void			put_dio_if_not_minus(long long di, t_flags *fl, t_b *base);
void			put_prec(long long int di, t_flags *fl, char *str);
int				padd_verify(t_flags *fl, long long int di);
void			check_flags_nb(t_flags *fl, unsigned long long int nb);

char			*join_all(char *s1, char *s2, char *s3);
int				ft_len_nb(long long int nb);
char			*ft_itoa_signed(long long int n);
ssize_t			cast_di(t_b *base, t_flags *fl);
size_t			cast_ou(t_b *base, t_flags *fl);
char			*ft_itoa_base(unsigned long long value, int base, t_flags *fl);
char			*hash_x_func(t_flags *fl, char *str, long long int x);
char			*ft_itoa_unsigned(unsigned long long int n);
void			del_str(char *s1, char *s2);
void			params_dio_minus(t_flags *fl, long long int di, t_b *base);

void			ft_ftoa(long double nb, t_b *base, t_flags *fl);
char			*ft_prec_f(char *fresh, t_b *base, t_flags *fl, long double nb);
char			*ft_make_str_f(t_b *base, t_flags *fl, char *str, char *fresh);
void			ft_point_prec(t_flags *fl, t_b *base, long long x);
void			ft_prec_s(t_flags *fl, t_b *base, char *s, char *ss);
int				ft_null(t_b *base, t_flags *fl);
char			*f_after_dot(t_flags *fl, long double nb);
long double		help_f(t_flags *fl, long double nb, long double d, t_b *base);

int				ft_printing_c(t_b *base, t_flags *fl);
int				ft_printing_s(t_b *base, t_flags *fl);
int				ft_printing_p(t_b *base, t_flags *fl);

#endif
