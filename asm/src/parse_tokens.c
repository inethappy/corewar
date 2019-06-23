/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 16:43:50 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/06/23 16:43:52 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

int		line_end(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
		return (-1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\0'
			&& line[i] != COMMENT_CHAR && line[i] != ALT_COMMENT_CHAR)
			j++;
		i++;
	}
	return (j);
}

void	save_inctructions(int fd, t_all *champ)
{
	char	*line;
	char	**token;
	int		flag;

	while (get_next_line(fd, &line))
	{
		flag = 0;
		champ->line_counter++;
		flag = line_end(line);
		token = ft_strsplit_new(line);
		if (token)
			parse_string_save_tokens(token, champ);
		else
			check_save_label(line, champ);
		del_arr(token);
		free(line);
	}
	if (flag > 0 && line == NULL)
		p_error("\nERROR! Unexpected end of input (Forgot a newline?)\n");
	free(line);
}

int		check_separator(char **token, int i, t_all *champ)
{
	int count;
	int cur;

	if (token[i][0] == SEPARATOR_CHAR && !token[i][1])
		return (1);
	count = find_cur_operation(token[i]);
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
			&& token[cur + 1][0] != '#' && token[cur + 1][0] != ';'
			&& token[cur + 1][0] != ',')
			error_in_line("ERROR! Invalid instruction", champ->line_counter);
		cur++;
	}
	return (1);
}

void	parse_string_save_tokens(char **token, t_all *champ)
{
	int i;
	int label;

	i = -1;
	label = 0;
	while (token[++i])
	{
		if (wrong_line(token, i, champ))
			error_in_line("ERROR! Invalid instruction", champ->line_counter);
		if (token[i][0] == COMMENT_CHAR || token[i][0] == ALT_COMMENT_CHAR)
			break ;
		if (detect_label(token[i], &label, champ))
			check_save_label(token[i], champ);
		else if (detect_instruction(token[i], champ))
			check_save_instr(ft_strsplit(token[i], SEPARATOR_CHAR), champ);
		else
		{
			if ((token[i + 1] && token[i + 1][0] == ',')
				|| !check_separator(token, i, champ))
				error_in_line("ERROR! Wrong instruction", champ->line_counter);
			check_save_op(token[i], champ);
		}
	}
}

void	parse_string_save_tokens_split(char **token, t_all *champ)
{
	int i;

	i = 0;
	while (token[i])
	{
		if (token[i][0] == COMMENT_CHAR || token[i][0] == ALT_COMMENT_CHAR)
			break ;
		if (token[i][0] == ':' && !champ->head)
			error_in_line("ERROR! Invalid instruction", champ->line_counter);
		else if (detect_instruction(token[i], champ))
			check_save_instr(ft_strsplit(token[i], SEPARATOR_CHAR), champ);
		else
		{
			if ((token[i + 1] && token[i + 1][0] == ',')
				|| !check_separator(token, i, champ))
				error_in_line("ERROR! Wrong instruction", champ->line_counter);
			check_save_op(token[i], champ);
		}
		i++;
	}
}
