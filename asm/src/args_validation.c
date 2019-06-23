/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:27:29 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/06/21 17:27:31 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

void	del_args_list(t_list *args)
{
	t_list *r;

	while (args)
	{
		r = args->next;
		del_list(args->content, args->content_size);
		free(args);
		args = r;
	}
}

void	check_arguments(t_list *all, t_token *cur, t_all *champ)
{
	int			i;
	t_token		*token;
	t_list		*args;

	args = NULL;
	i = find_cur_operation(cur->name);
	if (!champ->code)
		champ->code = ft_lstnew_new(&op_tab[i].code_op, 1);
	else
		ft_lstadd_end(champ->code, ft_lstnew_new(&op_tab[i].code_op, 1));
	champ->base->prog_size++;
	all = all->next;
	while (all)
	{
		token = all->content;
		if (token->type == 0 || token->type == 1)
			break ;
		add_list(&args, token);
		all = all->next;
	}
	is_correct_args(args, i, champ);
	if (op_tab[i].arg_size)
		save_args_code(args, champ);
	save_args(args, i, champ, cur);
	del_args_list(args);
}

void	is_correct_args(t_list *args, int op_nb, t_all *champ)
{
	int		count_args;
	t_token	*token;
	int		i;

	count_args = calculate_args(args);
	if (calculate_args(args) != op_tab[op_nb].arg_number)
		p_error("\nERROR! Wrong number of argument!\n");
	i = 0;
	while (args)
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

int		calculate_args(t_list *args)
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

void	is_existing_label(char *name, t_list *labels)
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
