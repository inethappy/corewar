#include "../asm.h"

int     is_register(char *token)
{
	int	i;

	if (token[0] != 'r' || !(ft_atoi(token + 1) > 0 && ft_atoi(token + 1) < 100))
		return (0);
	i = 1;
	while (token[i])
	{
		if (!ft_isdigit(token[i]))
			p_error("\nERROR! Invalid register.\n");
		else if (token[i] == COMMENT_CHAR || token[i] == ALT_COMMENT_CHAR)
			break ;
		i++;		
	}
	return (1);
}

t_list  *ft_lstnew_new(void *content, size_t content_size)
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