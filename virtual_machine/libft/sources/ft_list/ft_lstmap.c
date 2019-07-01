/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 03:07:18 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/23 21:03:39 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	head;
	t_list	*node;

	if ((lst == NULL) || (f == NULL))
		return (NULL);
	node = &head;
	while (lst != NULL)
	{
		node->next = (*f)(lst);
		node = node->next;
		lst = lst->next;
	}
	return (head.next);
}
