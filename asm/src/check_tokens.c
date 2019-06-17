#include "../asm.h"

void	check_save_instr(char **arg, t_all *champ)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		printf("tutb {%s}\n", arg[i]);
		if (ft_strchr(arg[i], '%') && arg[i][0] != '%')
		{
			del_arr(arg);
			return ; // for split ":%live:ld & etc"
		}
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
			error_in_line("POKA HZ", champ->line_counter);

			// p_error("POKA HZ\n");
		i++;
	}
	del_arr(arg);
}

void	check_save_label(char *line, t_all *champ)
{
	int		i;
	t_token	*ptr;

	i = 0;
	ptr = NULL;
	while(line[i])
	{
		if ((!ft_strchr(LABEL_CHARS, line[i]) && line[i] != LABEL_CHAR)
			|| (line[i] == LABEL_CHAR && ptr && ptr->name))
			error_in_line("ERROR!  Invalid label", champ->line_counter);

			// p_error("\nERROR! Invalid label.\n"); /// at string... ?
		if (line[i] == LABEL_CHAR)
		{
			if (line[i + 1])
				return ; // for split "live:ld & etc"
			ptr = ft_memalloc(sizeof(t_token));
			ptr->name = ft_strnew(i);
			ft_strncpy(ptr->name, line, i);
			ptr->step = champ->byte_counter;
			ptr->type = label;
		}
		i++;
	}
	if (ft_strlen(ptr->name) == 0)
		error_in_line("ERROR!  Invalid label", champ->line_counter);
		// p_error("\nERROR! Invalid label.\n");
	add_list(&champ->labels, ptr);
}

void	check_save_op(char *instr, t_all *champ)
{
	int		i;
	t_token	*ptr;

	i = -1;
	while (++i < 16)
		if (ft_strequ(instr, op_tab[i].name))
			break ;
	// printf("--- %s +++%s\n", op_tab[i].name, instr);
	if (i == 16)
		error_in_line("ERROR! Invalid operation", champ->line_counter);
		// p_error("\nERROR! Invalid operation.\n");
	ptr = ft_memalloc(sizeof(t_token));
	ptr->name = ft_strdup(instr);
	ptr->type = op;
	ptr->step = champ->byte_counter;
	champ->tdir_size_cur = (op_tab[i].tdir_size == 1) ? 2 : 4;
	// printf("--- %s %d\n", op_tab[i].name, op_tab[i].arg_size);
	champ->byte_counter += (op_tab[i].arg_size == 1) ? 2 : 1;
	add_list(&champ->head, ptr);
}
