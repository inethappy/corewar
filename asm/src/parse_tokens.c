#include "../asm.h"

void	save_inctructions(int fd,t_all *champ)
{
	char *line;
	char **token;

	while (get_next_line(fd, &line))
	{
		token = ft_strsplit_new(line);
		if (token)
			parse_string_save_tokens(token, champ);
		else
			check_save_label(line, champ);
		free(line);
		del_arr(token);
	}

	printf("name [%s]\ncomment [%s]\n", champ->base->prog_name, champ->base->comment);
	t_list *ll = champ->head;
	t_list *l = champ->labels;
	while (l)
	{
		t_token *t = l->content;
		printf("LABEL %10s step %5d type %5d\n", t->name, t->step, t->type);
		l = l->next;
	}
	while (ll)
	{
		t_token *tt = ll->content;
		printf("TOKEN %10s step %5d type %5d arg_type %5c\n", tt->name, tt->step, tt->type, tt->arg_type);
		ll = ll->next;
	}
}

void parse_string_save_tokens(char **token, t_all *champ)
{
	int i;
	int label;

	i = 0;
	label = 0;
	while (token[i])
	{
		// printf("after splitnew [%s]\n", token[i]);
		if (token[i][0] == '#')
			break ;
		if (ft_strchr(token[i], LABEL_CHAR) && *(ft_strchr(token[i], LABEL_CHAR) - 1) != '%')
		{
			if (label > 0)
				p_error("\nERROR! Invalid label.\n");
			check_save_label(token[i], champ);
			label++;
		}
		else if (ft_strchr(token[i], ',') || ft_strchr(token[i], '%') 
			|| is_register(token[i]) || ft_isdigit(token[i][0] || token[i][0] == '-'))
			check_save_instr(ft_strsplit(token[i], SEPARATOR_CHAR), champ);
		else
			check_save_op(token[i], champ);
		i++;
	}
}


