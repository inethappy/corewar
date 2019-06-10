#include "../asm.h"

void save_name(char *name, int fd, t_all *champ)
{
	char *line;

	if (!save_file_name(name, champ))
		p_error("\nERROR! Wrong file extension: only *.s please.\n");
	while (get_next_line(fd, &line))
	{
		if (line[0] == '.')
			check_name_comment(fd, line, champ);
		if (!ft_strchr(line, '"') && line[0] != '#' && line[0] != ';')
			break ;
		free(line);
	}
	free(line);
	// printf("TUT [%s] [%s]\n", champ->base->prog_name, champ->base->comment);
	// printf("name = [%s]\ncomment = [%s]", champ->name, champ->comment);
	if (champ->base->prog_name[0] == '\0' || champ->base->comment[0] == '\0')
		p_error("\nERROR! Name and comment of champion are needed.\n");
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

void	check_name_comment(int fd, char *line, t_all *champ)
{
	char **str;

	str = ft_strsplit_new(line);
	if (!str || (!ft_strstr(line, ".name") && !ft_strstr(line, ".comment")))//(!ft_strequ(str[0], ".name") && !ft_strequ(str[0], ".comment")))
		p_error("\nERROR! Invalid command.\n");
	if (ft_strstr(line, ".name"))//ft_strequ(str[0], ".name"))
		init_name(fd, champ, line);
	else if (ft_strstr(line, ".comment"))
		init_comment(fd, champ, line);
	del_arr(str);
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