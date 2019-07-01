/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 02:51:23 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/25 12:59:43 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstcut(t_list **lst, t_list *prev, void (*del)(void *, size_t))
{
	prev->next = (*lst)->next;
	ft_lstdelone(lst, del);
	*lst = prev->next;
}
