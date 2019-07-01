/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 01:51:15 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/25 12:38:46 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *node;

	if ((node = ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		node->content_size = 0;
		node->content = NULL;
	}
	else
	{
		if ((node->content_size = content_size) == 0)
			node->content = (void *)content;
		else
		{
			if ((node->content = ft_memalloc(content_size)) == NULL)
			{
				ft_memdel((void **)&node);
				return (NULL);
			}
			ft_memcpy(node->content, content, content_size);
		}
	}
	node->next = NULL;
	return (node);
}
