#include "../asm.h"

int line_end(char *line)
{
	int i = 0;
	int j = 0;

	if (line[i] == '\n' || line[i] == '\0')
		return 1;
	if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
		return -1;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\0'
			&& line[i] != COMMENT_CHAR && line[i] != ALT_COMMENT_CHAR)
			j++;
		i++;
	}
	return j;
}

void	save_inctructions(int fd,t_all *champ)
{
	char	*line;
	char	**token;
	int		flag;

	while (get_next_line(fd, &line))
	{
		flag = 0;
		champ->line_counter++;
				printf("---%s---\n", line);
			flag = line_end(line);
		if (flag == 0)
			break ;
		token = ft_strsplit_new(line);
		if (token)
		{
				printf("---%s---%d [%c]\n", line, flag, line[0]);
		// 	int y = -1;
		// 	while (token[++y])
			parse_string_save_tokens(token, champ);
		}
		else
			check_save_label(line, champ);
		free(line);
		del_arr(token);
	}
	// printf("{{%s}}\n", line);
	if (flag != -1 && line == NULL)
		p_error("\nERROR! Unexpected end of input (Forgot a newline?)\n");
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

int check_separator(char **token, int i, t_all *champ)
{
	int count;
	int cur;

	count = -1;
	while (++count < 16)
		if (ft_strstr(token[i], op_tab[count].name))
			break ;
	if (count == 16)
		error_in_line("ERROR! Invalid operation", champ->line_counter);
	if (op_tab[count].arg_number == 1)
		return (1);
	cur = i + 1;
	while (token[cur])
	{
		if (token[cur][0] == '#' || token[cur][0] == ';')
			break ;
		if (!ft_strchr(token[cur], ',') && token[cur + 1]
			&& token[cur + 1][0] != '#' && token[cur + 1][0] != ';' && token[cur + 1][0] != ',')
			error_in_line("ERROR! Invalid instruction", champ->line_counter);
		cur++;
	}
	return (1);
}

int detect_instruction(char *token, t_all *champ)
{
	char **new;
	char c;

	if (ft_strchr(token, ',') && (ft_strchr(token, ',') + 1)[0] == ',')
		error_in_line("ERROR! Invalid instruction", champ->line_counter);
	if ((ft_strchr(token, '%') && (ft_strchr(token, '%') - 1)[0] != ',' && token[0] != '%') || (ft_strchr(token, '-') && token[0] != '-'))
	{
		c = ft_strchr(token, '%') ? '%' : '-';
		new = ft_memalloc(sizeof(char*) * 2);
		new[0] = ft_strnew(ft_str_len_n(token, c));
		ft_strncpy(new[0], token, ft_str_len_n(token, c));
		new[1] = ft_strdup(token + ft_str_len_n(token, c));
		new[2] = NULL;
		parse_string_save_tokens_split(new, champ);
		del_arr(new);
		return (1);
	}
	else if (ft_strchr(token, ',') && (ft_strchr(token, ',') + 1)[0] != '\0')// && !ft_strchr((ft_strchr(token, ',') + 1), ','))
		return (1); //	поменяла этот элс с предидущим ифом местами
	else if (ft_strchr(token, '%') || is_register(token)
		|| ft_isdigit(token[0]) || token[0] == '-' || token[0] == ':') //add  token[0] == ':' for indir
		return (1);
	return (0);
}

int detect_label(char *token, int *label, t_all *champ)
{
	char **new;
	// printf("+===++%s\n", token);

	if (!ft_strchr(token, SEPARATOR_CHAR) && ft_strchr(token, LABEL_CHAR)
		&& *(ft_strchr(token, LABEL_CHAR) - 1) != '%' && token[0] != ':')
	{
		if (*(ft_strchr(token, LABEL_CHAR) + 1))
		{
			new = ft_strsplit(token, LABEL_CHAR);
			if (new[2])
				error_in_line("ERROR! Invalid label", champ->line_counter);
			del_arr(new);
			new = ft_memalloc(sizeof(char*) * 3);
			new[0] = ft_strnew(ft_str_len_n(token, ':') + 1);
			ft_strncpy(new[0], token, ft_str_len_n(token, ':') + 1);
			new[1] = ft_strdup(token + ft_str_len_n(token, ':') + 1);
			new[2] = NULL;
			parse_string_save_tokens(new, champ);
			del_arr(new);
			return (1);
		}
		*label += 1;
		if (*label > 1)
			error_in_line("ERROR! Invalid label", champ->line_counter);
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
		printf("=====[%s]\n", token[i]);
		if (token[i][0] == COMMENT_CHAR || token[i][0] == ALT_COMMENT_CHAR)
			break ;
		if ((token[i][ft_strlen(token[i]) - 1] == ','
			&& (!token[i + 1] || (token[i + 1][0] == ','))) || (token[i][0] == ':' && !champ->head))
			error_in_line("ERROR! Invalid instruction", champ->line_counter);
		if (detect_label(token[i], &label, champ))
			check_save_label(token[i], champ);
		else if (detect_instruction(token[i], champ))
			check_save_instr(ft_strsplit(token[i], SEPARATOR_CHAR), champ);
		else
		{
			if ((token[i + 1] && token[i + 1][0] == ',') || !check_separator(token, i, champ))
				error_in_line("ERROR! Invalid instruction", champ->line_counter);
			check_save_op(token[i], champ);
		}
		i++;
	}
}

void parse_string_save_tokens_split(char **token, t_all *champ)
{
	int i;

	i = 0;
	while (token[i])
	{
		printf("=====[%s]\n", token[i]);
		if (token[i][0] == COMMENT_CHAR || token[i][0] == ALT_COMMENT_CHAR)
			break ;
		if (token[i][0] == ':' && !champ->head)
			error_in_line("ERROR! Invalid instruction", champ->line_counter);
		else if (detect_instruction(token[i], champ))
			check_save_instr(ft_strsplit(token[i], SEPARATOR_CHAR), champ);
		else
		{
			if ((token[i + 1] && token[i + 1][0] == ',') || !check_separator(token, i, champ))
				error_in_line("ERROR! Invalid instruction", champ->line_counter);
			check_save_op(token[i], champ);
		}
		i++;
	}
}

