/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:53:30 by vkryvono          #+#    #+#             */
/*   Updated: 2019/03/16 14:53:59 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstfold(t_list *lst, void *(*f)(const void *, const void *, size_t))
{
	void	*res;

	res = NULL;
	while (lst != NULL)
	{
		res = (*f)(res, lst->content, lst->content_size);
		lst = lst->next;
	}
	return (res);
}
