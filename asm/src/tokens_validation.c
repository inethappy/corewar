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

void	save_args_code(t_list *args, t_all *champ)
{
	int		i;
	int		res;
	t_token	*arg;

	i = 0;
	res = 0;
	while (args)// && i < op_tab[op_nb].arg_number)
	{
		arg = args->content;
		if (arg->type == 2)
			res |= 64 >> 2 * i;
		else if (arg->type == 3 || arg->type == 5)
			res |= 128 >> 2 * i;
		else if (arg->type == 4 || arg->type == 6)
			res |= 192 >> 2 * i;
		i++;
		args = args->next;
	}
	// printf("YAYAYAYAYAY%d\n", res);
	ft_lstadd_end(champ->code, ft_lstnew(&res, 1));
	champ->base->prog_size++;

	// int *g = champ->code->next->content;
	// printf("YAYAYAYAYAY%x\n", *g);

}

int find_label(t_token *arg, t_list *lbls, t_token *cur)// t_all *champ)
{
	t_token	*token;

	while (lbls)
	{
		token = lbls->content;
		if (ft_strequ(token->name, arg->name))
		{
			// printf("[%s] [%s] [%s], [%d] [%d]\n", cur->name, token->name, arg->name, token->step, cur->step);
			return (token->step - cur->step);
		}
		lbls = lbls->next;
	}
	return (0);
}

void	save_args(t_list *args, int op_nb, t_all *champ, t_token *cur)
{
	t_token	*arg;
	int res;
	int tdir;

	tdir = (op_tab[op_nb].tdir_size == 1) ? 2 : 4;
	while (args)
	{
		arg = args->content;
		if (arg->type == 2)
		{
			res = ft_atoi(arg->name + 1);
			ft_lstadd_end(champ->code, ft_lstnew(&res, 1));
			champ->base->prog_size++;
		}
		else if (arg->type == 3)
		{
			res = ft_atoi(arg->name);
			ft_lstadd_end(champ->code, ft_lstnew(&res, tdir));
			champ->base->prog_size += tdir;
		}
		else if (arg->type == 5)
		{
			res = find_label(arg, champ->labels, cur);
			ft_lstadd_end(champ->code, ft_lstnew(&res, tdir));
			champ->base->prog_size += tdir;
		}
		else if (arg->type == 4)
		{
			res = ft_atoi(arg->name);
			ft_lstadd_end(champ->code, ft_lstnew(&res, 2));
			champ->base->prog_size += 2;
		}
		else if (arg->type == 6)
		{
			res = find_label(arg, champ->labels, cur);
			ft_lstadd_end(champ->code, ft_lstnew(&res, 2));
			champ->base->prog_size += 2;
		}
		args = args->next;
	}
}

void	check_arguments(t_list *all, t_token *cur, t_all *champ)
{
	int			i;
	t_token		*token;
	t_list		*args;

	args = NULL;
	i = -1;
	while (++i < 16)
		if (ft_strequ(cur->name, op_tab[i].name))
			break ;
	if (!champ->code)
		champ->code = ft_lstnew(&op_tab[i].code_op, 1);
	else
		ft_lstadd_end(champ->code, ft_lstnew(&op_tab[i].code_op, 1));
	champ->base->prog_size++;
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
	if (op_tab[i].arg_size)
		save_args_code(args, champ);
	save_args(args, i, champ, cur);
	// t_list *l;
	// l = champ->code;
	// while (l)
	// {
	// 	int *f = l->content;
	// 	printf("%d, %zu", *f, l->content_size);
	// 	l = l->next;
	// }
	// printf("%s [%d]\n", cur->name, cur->code->args_code);
	// ft_lstdel(&args, (void*)del_list);
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
	while (args)// && i < op_tab[op_nb].arg_number)
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
