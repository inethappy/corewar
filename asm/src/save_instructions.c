#include "../asm.h"

void set_instr_label(char *instr, t_all *champ, int i)
{
	t_token *ptr;

	ptr = ft_memalloc(sizeof(t_token));
	ptr->step = champ->byte_counter;
	champ->byte_counter += (i == 2) ? champ->tdir_size_cur : 2;
	ptr->type = (i == 2) ? dir_l : indir_l;
	ptr->arg_type = (i == 2) ? T_DIR : T_IND;
	ptr->name = (i == 2) ? ft_strdup(instr + 2) : ft_strdup(instr + 1);
	while (instr[i])
		if (!ft_strchr(LABEL_CHARS, instr[i++]))
			error_in_line("ERROR! Invalid instruction", champ->line_counter);

			// p_error("\nERROR! Invalid instrution.\n");
	add_list(&champ->head, ptr);
}

void set_instr_nb(char *instr, t_all *champ)
{
	t_token	*ptr;
	int		i;

	i = (instr[0] == '%') ? 1 : 0;
	ptr = ft_memalloc(sizeof(t_token));
	ptr->type = (i == 1) ? dir : indir;
	ptr->arg_type = (i == 1) ? T_DIR : T_IND;
	ptr->step = champ->byte_counter;
	champ->byte_counter += champ->tdir_size_cur;
	// printf("tututuut %s %d\n", instr, ft_atoi(instr + 1));
	i += (instr[i] == '-') ? 1 : 0;
	while (instr[i])
		if (!ft_isdigit(instr[i++]))
			error_in_line("ERROR! Invalid instruction", champ->line_counter);

			// p_error("\nERROR! Invalid instrution.\n");
	ptr->name = (ptr->type == 3) ? ft_strdup(instr + 1) : ft_strdup(instr);
	add_list(&champ->head, ptr);
}

void			set_instr_reg(char *arg, t_all *champ)
{
	t_token	*ptr;

	ptr = ft_memalloc(sizeof(t_token));
	ptr->name = ft_strdup(arg);
	ptr->type = reg;
	ptr->arg_type = T_REG;
	ptr->step = champ->byte_counter;
	champ->byte_counter++;
	add_list(&champ->head, ptr);
}
