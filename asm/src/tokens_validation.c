#include "../asm.h"

void    tokens_validation(t_list *all, t_all *champ)
{
	t_token	*cur;

	if (!all && !champ->labels)
		p_error("\nERROR! No operations found!\n");
	while (all)
	{
		cur = all->content;
		if (cur->type == 1)
			check_arguments(all, cur, champ);
		all = all->next;
	}
}

void	check_arguments(t_list *all, t_token *cur, t_all *champ)
{
	int		i;
	t_token	*token;
	t_list	*args;

	args = NULL;
	i = -1;
	while (++i < 16)
		if (ft_strequ(cur->name, op_tab[i].name))
			break ;
	all = all->next;
	while (all)
	{
		token = all->content;
		if (token->type == 0 || token->type == 1)
			break ;
		add_list(&args, token);
		// printf("%s[%c][%d][%d]\n", token->name, op_tab[i].arg[0], op_tab[i].arg[1], op_tab[i].arg[2]);
		all = all->next;
	}
	is_correct_args(args, i, champ);
	ft_lstdel(&args, (void*)del_list);
}

void is_correct_args(t_list *args, int op_nb, t_all *champ)
{
	int		count_args;
	t_token	*token;
	int		i;

	count_args = calculate_args(args);
	if (calculate_args(args) != op_tab[op_nb].arg_number)
		p_error("\nERROR! Wrong number of argument!\n");
	i = 0;
	while (args && i < op_tab[op_nb].arg_number)
	{
		token = args->content;
		if ((token->arg_type & op_tab[op_nb].arg[i]) == 0)
			p_error("\nERROR! Wrong argument in operation!\n");
		if (token->type == 5 || token->type == 6)
			is_existing_label(token->name, champ->labels);
		i++;
		args = args->next;
	}
}

int calculate_args(t_list *args)
{
	int i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}

void is_existing_label(char *name, t_list *labels)
{
	t_token *label;

	while (labels)
	{
		label = labels->content;
		if (ft_strequ(label->name, name))
			return ;
		labels = labels->next;
	}
	p_error("ERROR! Wrong label in operation!\n");
}





