#include "../asm.h"

void	init_name(int fd, t_all *champ, char *line)
{
	char *buf;
	if (champ->base->prog_name[0] != '\0')
		p_error("\nERROR! Invalid command.\n");
	buf = save_command_data(fd, line, 4);
	if (ft_strlen(buf) > PROG_NAME_LENGTH)
		p_error("\nERROR! Too long name. Max length = 128\n");		
	ft_strcpy(champ->base->prog_name, buf);
	free(buf);
}

void	init_comment(int fd, t_all *champ, char *line)
{
	char *buf;

	if (champ->base->comment[0] != '\0')
		p_error("\nERROR! Invalid command.\n");
	buf = save_command_data(fd, line, 7);
	if (ft_strlen(buf) >  COMMENT_LENGTH)
		p_error("\nERROR! Too long comment. Max length = 2048\n");
	ft_strcpy(champ->base->comment, buf);
	free(buf);
}

char *save_end_of_command(char *buf, char *line, char *str)
{
	int		i;

	i = 0;
	while (line[i] != '"')
		i++;
	check_tail(line + i + 1);
	buf = ft_strnew(i + 1);
	ft_strncpy(buf, line, i);
	buf[ft_strlen(buf) - 1] = '\n';
	free(line);
	line = ft_strjoin(str, buf);
	// printf("[%s] [%s] {%c} [%s]\n", line, buf, buf[0], str);
	free(str);
	free(buf);
	return (line);
}

char *find_string_tail(char *str, char *line, int fd)
{
	char	*buf;

	buf = NULL;
	while (get_next_line(fd, &line))
	{
		if (ft_strchr(line, '"'))
		{
			// printf("LLL %s\n", line);
			line = save_end_of_command(buf, line, str);
			break ;
		}
		else
		{
			buf = ft_strjoin(str, line);
			free(str);
			str = ft_strdup(buf);
			free(buf);
		}
		free(line);
	}
	// printf("LLL %s\n", line);
	return (line);
}

char 	*save_command_data(int fd, char *line, int index)
{
	int		i;
	char	*str;

	while (line[++index] != '"')
		if (line[index] != ' ' && line[index] != '\t')
			p_error("\nERROR! Invalid data in command line.\n");
	i = index;
	while (line[++i] != '"')
	if (line[i] == '\0')
		if ((str = find_string_tail(ft_strjoin(ft_strdup(line + index + 1), "\n"), line, fd)))
			return (str);
	check_tail(line + i + 1);
	str = ft_strnew(i - index + 1);
	ft_strncpy(str, (line + (index + 1)), ((i - 1) - index));
	// printf("str =  %s line = [%s]\n", str, line);
	return (str);
}