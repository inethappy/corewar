/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:24:38 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/06/21 17:24:39 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

void	tokens_validation(t_list *all, t_all *champ)
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
	while (args)
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
	ft_lstadd_end(champ->code, ft_lstnew(&res, 1));
	champ->base->prog_size++;
}

int		find_label(t_token *arg, t_list *lbls, t_token *cur)
{
	t_token	*token;

	while (lbls)
	{
		token = lbls->content;
		if (ft_strequ(token->name, arg->name))
			return (token->step - cur->step);
		lbls = lbls->next;
	}
	return (0);
}

void	save_args(t_list *args, int op_nb, t_all *champ, t_token *cur)
{
	t_token	*arg;
	int		res;
	int		tdir;
	int		size;

	tdir = (op_tab[op_nb].tdir_size == 1) ? 2 : 4;
	while (args)
	{
		arg = args->content;
		if (arg->type == 2 && (size = 1))
			res = ft_atoi(arg->name + size);
		else if (arg->type == 3 && (size = tdir))
			res = ft_atoi(arg->name);
		else if (arg->type == 5 && (size = tdir))
			res = find_label(arg, champ->labels, cur);
		else if (arg->type == 4 && (size = 2))
			res = ft_atoi(arg->name);
		else if (arg->type == 6 && (size = 2))
			res = find_label(arg, champ->labels, cur);
		ft_lstadd_end(champ->code, ft_lstnew(&res, size));
		champ->base->prog_size += size;
		args = args->next;
	}
}

int		find_cur_operation(char *name)
{
	int	i;

	i = -1;
	while (++i < 16)
		if (ft_strequ(name, op_tab[i].name))
			break ;
	return (i);
}
