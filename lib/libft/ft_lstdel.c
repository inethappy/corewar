/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:41:56 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/11/09 19:23:21 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*lst;
	t_list	*nlst;

	lst = *alst;
	while (lst)
	{
		nlst = lst->next;
		del(lst->content, lst->content_size);
		free(lst);
		lst = nlst;
	}
	*alst = NULL;
}
