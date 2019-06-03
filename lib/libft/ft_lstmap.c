/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:37:38 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/11 18:44:32 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *begin;
	t_list *new;
	t_list *tmp2;

	tmp2 = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst->next)
	{
		new = f(lst);
		new->next = f(lst->next);
		if (tmp2)
		{
			tmp2->next = new;
			tmp2 = tmp2->next;
		}
		else
		{
			tmp2 = new;
			begin = new;
		}
		lst = lst->next;
	}
	return (begin);
}
