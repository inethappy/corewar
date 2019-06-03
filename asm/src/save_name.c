#include "../asm.h"

void save_name(char *name, int fd, t_all *champ)
{
	char *line;

	if (!save_file_name(name, champ))
		p_error("\nERROR! Wrong file extension: only *.s please.\n");
	while (get_next_line(fd, &line))
	{
		if (line[0] == '.')
			parse_string_save_data(line, champ);
		if (!ft_strchr(line, '"') && line[0] != '#' && line[0] != ';')
			break ;
		free(line);
	}
	free(line);
	// printf("name = [%s]\ncomment = [%s]", champ->name, champ->comment);
	if (!champ->name || !champ->comment)
		p_error("\nERROR! Name and comment of champion are needed.\n");
	if (ft_strlen(champ->name) > PROG_NAME_LENGTH 
		|| ft_strlen(champ->comment) > COMMENT_LENGTH)
		p_error("\nERROR! Too long command line. Max length .name = 128, .comment = 2048\n");
}

int save_file_name(char *f_name, t_all *champ)
{
	int		i;
	char	*name;
	char	**fn;

	fn = ft_strsplit(f_name, '/');
	if (!fn)
		name = f_name;
	else
	{
		i = -1;
		while (fn[++i])
			if (!fn[i + 1])
				name = ft_strdup(fn[i]);
	}	
	if (name[ft_strlen(name) - 2] != '.' || name[ft_strlen(name) - 1] != 's')
		return (0);
	champ->file_name = ft_strnew(ft_strlen(name) + 2);
	ft_strncpy(champ->file_name, name, ft_strlen(name) - 2);
	ft_strcpy((champ->file_name + ft_strlen(champ->file_name)), ".cor");
	del_arr(fn);
	free(name);
	// printf("file name [%s]\n",champ->file_name);
	return (1);
}

void parse_string_save_data(char *line, t_all *champ)
{
	int		i;

	i = 0;
	char **str;
	str = NULL;

	str = ft_strsplit_new(line);
	if (!str || (!ft_strequ(str[0], ".name") && !ft_strequ(str[0], ".comment")))
		p_error("\nERROR! Invalid command.");
	// printf("TUT %s\n", str[1]);
	if (ft_strequ(str[0], ".name"))
		champ->name = save_command_data(line, 5);
	else
		champ->comment = save_command_data(line, 8);
	del_arr(str);
}

char *save_command_data(char *line, int index)
{
	int		i;
	char	*str;

	while (line[index++] != '\n')
	{
		if (line[index] == '"')
			break;
		else if (line[index] != ' ' && line[index] != '\t')
			p_error("\nERROR! Invalid data in command line.\n");
	}
	i = index;
	while (line[++i])// != '\n')
	{
		if (line[i] == '"')
			break;
	}
	if (line[i] == '\n' || line[i] == '\0' || check_tail(line + i + 1))
		p_error("\nERROR! Invalid data in command line.\n");
	str = ft_strnew(i - index + 1);
	ft_strncpy(str, (line + (index + 1)), ((i - 1) - index));
	// printf("str =  %s\n", str);

	return (str);
}

int check_tail(char *line)
{
	while (*line)
	{
		if (*line == '#' || *line == ';')
			break;
		else if (*line != ' ' && *line != '\t')
			p_error("\nERROR Invalid data in command line.\n");
		++*line++;
	}
	return 0;
}