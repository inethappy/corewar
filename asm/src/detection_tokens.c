#include "../asm.h"

int		detect_instruction(char *token, t_all *champ)
{
	char **new;
	char c;

	c = 0;
	if (ft_strchr(token, ',') && (ft_strchr(token, ',') + 1)[0] == ',')
		error_in_line("ERROR! Invalid instruction", champ->line_counter);
	else if (ft_strchr(token, ',') && (ft_strchr(token, ',') + 1)[0] != '\0')
		return (1); //	поменяла этот элс с предидущим ифом местами
	if ((ft_strchr(token, '%') && (ft_strchr(token, '%') - 1)[0] != ',' && token[0] != '%') || (ft_strchr(token, '-') && token[0] != '-' && token[0] != '%'))
	{
		if ((ft_strchr(token, '%') && (ft_strchr(token, '%') - 1)[0] != ',' && token[0] != '%') || (token[0] == '%' && ft_strchr(token, '-')))
			c = '%';
		else if (ft_strchr(token, '-') && token[0] != '-')
			c = '-';
		new = ft_memalloc(sizeof(char*) * 2);
		new[0] = ft_strnew(ft_str_len_n(token, c));
		ft_strncpy(new[0], token, ft_str_len_n(token, c));
		new[1] = ft_strdup(token + ft_str_len_n(token, c));
		new[2] = NULL;
		parse_string_save_tokens_split(new, champ);
		del_arr(new);
		return (1);
	}
	else if (ft_strchr(token, '%') || is_register(token)
		|| ft_isdigit(token[0]) || token[0] == '-' || token[0] == ':')
		return (1);
	return (0);
}


// int detect_instruction(char *token, t_all *champ)
// {
// 	char **new;
// 	char c;

// 	if (ft_strchr(token, ',') && (ft_strchr(token, ',') + 1)[0] == ',')
// 		error_in_line("ERROR! Invalid instruction", champ->line_counter);
// 	if ((ft_strchr(token, '%') && (ft_strchr(token, '%') - 1)[0] != ',' && token[0] != '%') || (ft_strchr(token, '-') && token[0] != '-'))
// 	{
// 		c = ft_strchr(token, '%') ? '%' : '-';
// 		new = ft_memalloc(sizeof(char*) * 2);
// 		new[0] = ft_strnew(ft_str_len_n(token, c));
// 		ft_strncpy(new[0], token, ft_str_len_n(token, c));
// 		new[1] = ft_strdup(token + ft_str_len_n(token, c));
// 		new[2] = NULL;
// 		parse_string_save_tokens_split(new, champ);
// 		del_arr(new);
// 		return (1);
// 	}
// 	else if (ft_strchr(token, ',') && (ft_strchr(token, ',') + 1)[0] != '\0')// && !ft_strchr((ft_strchr(token, ',') + 1), ','))
// 		return (1); //	поменяла этот элс с предидущим ифом местами
// 	else if (ft_strchr(token, '%') || is_register(token)
// 		|| ft_isdigit(token[0]) || token[0] == '-' || token[0] == ':') //add  token[0] == ':' for indir
// 		return (1);
// 	return (0);
// }

int		detect_label(char *token, int *label, t_all *champ)
{
	char **new;

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
