#include "../asm.h"
// ../vm_champs/asm ../vm_champs/champs/toto_test.s && xxd ../vm_champs/champs/toto_test.cor > ../asm/car.bt


int main(int argc, char **argv)
{
	t_all	*champ;
	int		fd;

	if (argc != 2)
		p_error("\n\tInvalid input arguments.\nPlease use the following structure:\n\t./asm champion_file.s\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		p_error("\nERROR! Not valid file.\n");
	champ = ft_memalloc(sizeof(t_all));
	champ->base = ft_memalloc(sizeof(headers_t));
	save_name(argv[1], fd, champ);
	save_inctructions(fd, champ);
	system("leaks asm > leaks.txt");
	return 0;	
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

void check_save_label(char *line, t_all *champ)
{
	int		i;
	t_token	*ptr;

	i = 0;
	ptr = ft_memalloc(sizeof(t_token));
	while(line[i])
	{
		if ((!ft_strchr(LABEL_CHARS, line[i]) && line[i] != LABEL_CHAR) 
			|| (line[i] == LABEL_CHAR && ptr->name))
			p_error("\nERROR! Invalid label.\n"); /// at string... ?
		if (line[i] == LABEL_CHAR)//ft_strchr(line, LABEL_CHAR))
		{
			ptr->name = ft_strnew(i);
			ft_strncpy(ptr->name, line, i);
			ptr->step = champ->byte_counter;
			ptr->type = label;
		}
		i++;
	}
	if (!champ->head)
		champ->head = ft_lstnew_new(ptr, sizeof(t_token));
	else
		ft_lstadd_end(champ->head, ft_lstnew_new(ptr, sizeof(t_token)));
}

int is_register(char *token)
{
	int	i;

	if (token[0] != 'r' || !(ft_atoi(token + 1) > 0 && ft_atoi(token + 1) < 17))
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

void set_instr_label(char *instr, t_all *champ, int i)
{
	t_token *ptr;
	
	ptr = ft_memalloc(sizeof(t_token));
	ptr->step = champ->byte_counter;
	champ->byte_counter += (i == 2) ? champ->tdir_size_cur : 2;
	ptr->type = (i == 2) ? dir_l : indir_l;
	while (instr[i])
		if (!ft_strchr(LABEL_CHARS, instr[i++]))
			p_error("\nERROR! Invalid instrution.\n");
	ptr->name = ft_strdup(instr + 2);
	if (!champ->head)
		champ->head = ft_lstnew_new(ptr, sizeof(t_token));
	else
		ft_lstadd_end(champ->head, ft_lstnew_new(ptr, sizeof(t_token)));
}

void set_instr_nb(char *instr, t_all *champ)
{
	t_token	*ptr;
	int		i;

	i = (instr[0] == '%') ? 1 : 0;
	ptr = ft_memalloc(sizeof(t_token));
	ptr->type = (i == 1) ? dir : indir;
	ptr->step = champ->byte_counter;
	champ->byte_counter += champ->tdir_size_cur;
	// printf("tututuut %s %d\n", instr, ft_atoi(instr + 1));
	i += (instr[i] == '-') ? 1 : 0;
	while (instr[i])
		if (!ft_isdigit(instr[i++]))
			p_error("\nERROR! Invalid instrution.\n");	
	ptr->name = (ptr->type == 3) ? ft_strdup(instr + 1) : ft_strdup(instr);
	if (!champ->head)
		champ->head = ft_lstnew_new(ptr, sizeof(t_token));
	else
		ft_lstadd_end(champ->head, ft_lstnew_new(ptr, sizeof(t_token)));
}

void			set_instr_reg(char *arg, t_all *champ)
{
	t_token	*ptr;

	ptr = ft_memalloc(sizeof(t_token));
	ptr->name = ft_strdup(arg);
	ptr->type = reg;
	ptr->step = champ->byte_counter;
	champ->byte_counter++;
	if (!champ->head)
		champ->head = ft_lstnew_new(ptr, sizeof(t_token));
	else
		ft_lstadd_end(champ->head, ft_lstnew_new(ptr, sizeof(t_token)));
}

void check_save_instr(char **arg, t_all *champ)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		printf("tutb {%s}\n", arg[i]);
		if (is_register(arg[i]))
			set_instr_reg(arg[i], champ);
		else if (arg[i][0] == '%' && arg[i][1] == ':')
			set_instr_label(arg[i], champ, 2);
		else if (arg[i][0] == ':')
			set_instr_label(arg[i], champ, 1);
		else if ((arg[i][0] == '%' && (ft_isdigit(arg[i][1]) || arg[i][1] == '-')) 
			|| ft_isdigit(arg[i][0]) || arg[i][0] == '-')
			set_instr_nb(arg[i], champ);
		else
			p_error("ffmmf\n");
		i++;
	}
	// printf("INSTR %s\n", arg[i]);
}

void check_save_op(char *instr, t_all *champ)
{
	int i;
	t_token *ptr;

	i = 0;
	while (i++ < 16)
		if (ft_strequ(instr, op_tab[i].name))
			break ;
	// printf("op =  %s\n", instr);
	ptr = ft_memalloc(sizeof(t_token));
	ptr->name = ft_strdup(instr);
	ptr->type = op;
	ptr->step = champ->byte_counter;
	champ->tdir_size_cur = (op_tab[i].tdir_size == 1) ? 2 : 4;
	// printf("--- %s %d\n", op_tab[i].name, op_tab[i].arg_size);
	champ->byte_counter += (op_tab[i].arg_size == 1) ? 2 : 1;
	if (!champ->head)
		champ->head = ft_lstnew_new(ptr, sizeof(t_token));
	else
		ft_lstadd_end(champ->head, ft_lstnew_new(ptr, sizeof(t_token)));
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

void	save_inctructions(int fd,t_all *champ)
{
	char *line;
	char **token;

	while (get_next_line(fd, &line))
	{
		// printf("before splitnew [%s]\n", line);
		token = ft_strsplit_new(line);
		if (token)
			parse_string_save_tokens(token, champ);
		else
			check_save_label(line, champ);
	}
	// printf("kfkfkfkfkkf\n");

	t_list *ll = champ->head;
	while (ll)
	{
		t_token *tt = ll->content;
		printf("LABEL %10s step %5d type %5d\n", tt->name, tt->step, tt->type);
		ll = ll->next;
	}
}
