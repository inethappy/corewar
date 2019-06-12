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
	free(line);

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
		printf("TOKEN %10s step %5d type %5d arg_type %5d\n", tt->name, tt->step, tt->type, tt->arg_type);
		ll = ll->next;
	}
}

int check_separator(char **token, int i)
{
	int count;
	int cur;

	count = -1;
	while (++count < 16)
		if (ft_strstr(token[i], op_tab[count].name))
			break ;
	if (count == 16)
		p_error("\nERROR! Invalid operation.\n");
	if (op_tab[count].arg_number == 1)
		return (1);
	cur = i + 1;

	while (token[cur])
	{

		if (token[cur][0] == '#')
			break ;
		if (!ft_strchr(token[cur], ',') && token[cur + 1]
			&& token[cur + 1][0] != '#' && token[cur + 1][0] != ',')
			p_error("\nERROR! Invalid instruction.\n");

		cur++;
	}

	return (1);
}

int detect_instruction(char *token)
{
	if (ft_strchr(token, ',') && (ft_strchr(token, ',') + 1)[0] == ',')
		p_error("\nERROR! Invalid instruction.\n");
	if (ft_strchr(token, ','))// && !ft_strchr((ft_strchr(token, ',') + 1), ','))
		return (1);
	if (ft_strchr(token, '%') || is_register(token)
		|| ft_isdigit(token[0]) || token[0] == '-')
		return (1);

	return (0);
}

int detect_label(char *token, int *label)
{
	if (ft_strchr(token, LABEL_CHAR) && *(ft_strchr(token, LABEL_CHAR) - 1) != '%')
	{
		*label += 1;
		if (*label > 1)
		p_error("\nERROR! Invalid label.\n");
		return (1);
	}
	return (0);
}

void parse_string_save_tokens(char **token, t_all *champ)
{
	int i;
	int label;

	i = 0;
	label = 0;
	while (token[i])
	{

		if (token[i][0] == '#')
			break ;
		if (token[i][ft_strlen(token[i]) - 1] == ',' && (!token[i + 1] || (token[i + 1][0] == ',')))
				p_error("\nERROR! Invalid instruction.\n");
		if (detect_label(token[i], &label))
			check_save_label(token[i], champ);
		else if (detect_instruction(token[i]))
			check_save_instr(ft_strsplit(token[i], SEPARATOR_CHAR), champ);
		else
		{
			if (token[i + 1][0] == ',' || !check_separator(token, i))
				p_error("\nERROR! Invalid instruction.\n");

			check_save_op(token[i], champ);
		}
		i++;
	}
}


