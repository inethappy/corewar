/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:54:40 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 14:35:53 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "ft_printf.h"

# define ABS(Value) ((Value) >= 0 ? (Value) : -(Value))
# define IS_NEGATIVE(Value) ((Value) < 0 ? 1 : 0)
# define LL_MAX 9223372036854775807

# define BUFF_SIZE 33

# define READ 1
# define COMPLETE 0
# define ERR -1

/*
**	For wchar_t converting
**	mask0 = 0xxxxxxx
**	mask1 = 110xxxxx 10xxxxxx
**	mask2 = 1110xxxx 10xxxxxx 10xxxxxx
**	mask3 = 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

# define MASK_1 (unsigned int)0b00000000
# define MASK_2 (unsigned int)0b1100000010000000
# define MASK_3 (unsigned int)0b111000001000000010000000
# define MASK_4 (unsigned int)0b11110000100000001000000010000000

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);

void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *s1, const void *s2, int c, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

unsigned short		ft_swap16(unsigned short val);
unsigned int		ft_swap32(unsigned int val);
unsigned long long	ft_swap64(unsigned long long val);

int					ft_endian(void);
uintmax_t			ft_htob(uintmax_t host, size_t size);
uintmax_t			ft_btoh(uintmax_t host, size_t size);
uintmax_t			ft_htol(uintmax_t host, size_t size);
uintmax_t			ft_ltoh(uintmax_t host, size_t size);

size_t				ft_strlen(const char *s);
size_t				ft_strslen(const char *s);
char				*ft_strdup(const char *s1);

char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);

char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);

char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
								size_t len);

int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

size_t				ft_wctomb(char **buff, unsigned int c);
char				*ft_widetostr(wchar_t *wstr);
char				*ft_widetrim(char **buff);

int					ft_atoi(const char *str);
int					ft_atoi16(const char *str);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_iswhspace(int c);

int					ft_toupper(int c);
int					ft_tolower(int c);

char				*ft_strtoupper(char *str);
char				*ft_strtolower(char *str);

void				*ft_memalloc(size_t size);
void				*ft_realloc(void **memory,
										size_t old_size, size_t new_size);
void				ft_memdel(void **ap);

char				*ft_strnew(size_t size);
void				ft_strdel(char **s);

void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);

char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strappend(char **s1, char **s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
int					ft_strsplitlen(char **str);
char				*ft_itoa(int n);
char				*ft_uitoabase(uintmax_t num, int base);
char				*ft_itoabase(intmax_t num, int base);

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstcut(t_list **lst, t_list *prev,
											void (*del)(void *, size_t));
void				ft_lstappend(t_list **alst, t_list *new);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
size_t				ft_lstlen(t_list *lst);
t_list				*ft_lsttail(t_list *lst);
void				ft_lstrm(void *content, size_t content_size);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				*ft_lstfold(t_list *lst,
								void *(*f)(const void *, const void *, size_t));
t_list				*ft_lstfind(t_list *lst, void const *content,
								int (*cmp)(void const *, void const *));

int					get_next_line(const int fd, char **line);

int					ft_isfile(const char *path);
int					ft_isdir(const char *path);
size_t				ft_filesize(const char *path);

size_t				ft_getfile(char *path, char **file);
size_t				ft_getstdin(char **str);

#endif
