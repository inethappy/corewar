/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:59:52 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/06/21 15:59:54 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

void	check_save_instr(char **arg, t_all *champ)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '\0' || (ft_strchr(arg[i], '%') && arg[i][0] != '%')
			|| (ft_strchr(arg[i], '-') && arg[i][0] != '-' && arg[i][1] != '-'))
		{
			del_arr(arg);
			return ;
		}
		if (is_register(arg[i]))
			set_instr_reg(arg[i], champ);
		else if (arg[i][0] == '%' && arg[i][1] == ':')
			set_instr_label(arg[i], champ, 2);
		else if (arg[i][0] == ':')
			set_instr_label(arg[i], champ, 1);
		else if ((arg[i][0] == '%' && (ft_isdigit(arg[i][1])
			|| arg[i][1] == '-')) || ft_isdigit(arg[i][0]) || arg[i][0] == '-')
			set_instr_nb(arg[i], champ);
		else
			error_in_line("ERROR!", champ->line_counter);
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
	while (line[i])
	{
		if ((!ft_strchr(LABEL_CHARS, line[i]) && line[i] != LABEL_CHAR)
			|| (line[i] == LABEL_CHAR && ptr && ptr->name))
			error_in_line("ERROR!  Invalid label", champ->line_counter);
		if (line[i] == LABEL_CHAR)
		{
			if (line[i + 1])
				return ;
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
	add_list(&champ->labels, ptr);
}

void	check_save_op(char *instr, t_all *champ)
{
	int		i;
	t_token	*ptr;

	i = -1;
	if (instr[0] == SEPARATOR_CHAR && !instr[1])
		return ;
	while (++i < 16)
		if (ft_strequ(instr, op_tab[i].name))
			break ;
	if (i == 16)
		error_in_line("ERROR! Invalid operation", champ->line_counter);
	ptr = ft_memalloc(sizeof(t_token));
	ptr->name = ft_strdup(instr);
	ptr->type = op;
	ptr->step = champ->byte_counter;
	champ->tdir_size_cur = (op_tab[i].tdir_size == 1) ? 2 : 4;
	champ->byte_counter += (op_tab[i].arg_size == 1) ? 2 : 1;
	add_list(&champ->head, ptr);
}

int		wrong_line(char **token, int i, t_all *champ)
{
	if (token[i][0] == SEPARATOR_CHAR && !token[i][1]
		&& token[i + 1] && (token[i + 1][0] == COMMENT_CHAR
		|| token[i + 1][0] == ALT_COMMENT_CHAR))
		return (1);
	if (token[i][0] == COMMENT_CHAR || token[i][0] == ALT_COMMENT_CHAR)
		return (0);
	if ((token[i][ft_strlen(token[i]) - 1] == ',' && (!token[i + 1]
			|| (token[i + 1][0] == ',')))
			|| (token[i][0] == ':' && !champ->head))
		return (1);
	return (0);
}
