/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:42:01 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/06/21 15:42:03 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

void	add_list(t_list **list, void *ptr)
{
	if (!*list)
		*list = ft_lstnew_new(ptr, sizeof(t_token));
	else
		ft_lstadd_end(*list, ft_lstnew_new(ptr, sizeof(t_token)));
}

int		is_register(char *token)
{
	int	i;

	if (token[0] != 'r' || !(ft_atoi(token + 1) >= 0
		&& ft_atoi(token + 1) < 100))
		return (0);
	i = 1;
	while (token[i])
	{
		if (!ft_isdigit(token[i]))
			p_error("\nERROR! Invalid register.\n");
		else if (token[i] == COMMENT_CHAR || token[i] == ALT_COMMENT_CHAR)
			break ;
		i++;
		return (1);
	}
	return (0);
}

t_list	*ft_lstnew_new(void *content, size_t content_size)
{
	t_list	*new;

	new = NULL;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = content;
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}

void	del_list(t_token *token, size_t content_size)
{
	content_size = 0;
	free(token->name);
	free(token);
}

void	error_in_line(char *err, int line)
{
	if (line)
		ft_printf("\n%s in line '%d'\n\n", err, line);
	else
		ft_printf("\n%s\n", err);
	exit(1);
}
