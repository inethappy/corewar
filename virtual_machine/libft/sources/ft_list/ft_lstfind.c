/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:42:37 by vkryvono          #+#    #+#             */
/*   Updated: 2019/03/16 17:42:50 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void const *content,
								int (*cmp)(void const *, void const *))
{
	while (lst != NULL)
	{
		if (cmp(lst->content, content))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
