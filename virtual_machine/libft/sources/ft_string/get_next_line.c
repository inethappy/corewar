/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:46:38 by vkryvono          #+#    #+#             */
/*   Updated: 2019/01/13 04:36:25 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_get_file(int fd, t_list **head)
{
	t_list	*tmp;

	if (fd < 0)
		return (NULL);
	if (!(*head))
	{
		*head = (t_list *)ft_memalloc(sizeof(t_list));
		(*head)->content_size = (size_t)fd;
		(*head)->content = NULL;
		(*head)->next = NULL;
		return (*head);
	}
	tmp = *head;
	while (tmp->next && (fd != (int)tmp->content_size))
		tmp = tmp->next;
	if (fd != (int)tmp->content_size)
	{
		tmp->next = (t_list *)ft_memalloc(sizeof(t_list));
		tmp = tmp->next;
		tmp->content_size = (size_t)fd;
		tmp->content = NULL;
		tmp->next = NULL;
	}
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*offcut;
	t_list			*curr;
	char			buff[BUFF_SIZE + 1];
	int				len;
	char			*tmp;

	if ((BUFF_SIZE < 0) || (!line) || !(curr = ft_get_file(fd, &offcut)))
		return (ERR);
	len = BUFF_SIZE;
	while (((tmp = ft_strchr(curr->content, '\n')) == NULL) && (len > 0))
	{
		if ((len = (int)read(fd, buff, BUFF_SIZE)) < 0)
			return (ERR);
		buff[len] = '\0';
		tmp = curr->content;
		curr->content = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
	}
	*line = (tmp) ? ft_strsub(curr->content, 0, (tmp - (char *)curr->content))
			: curr->content;
	tmp = (tmp) ? ft_strdup(tmp + 1) : NULL;
	if (tmp)
		ft_strdel((char **)&(curr->content));
	curr->content = tmp;
	return (ft_strlen(*line) || (curr->content != NULL));
}
