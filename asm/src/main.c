#include "../asm.h"
// ./vm_champs/asm ./vm_champs/champs/toto_test.s && xxd ./vm_champs/champs/toto_test.cor > ./asm/car.bt
t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

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
	// printf("file name [%s]\n",champ->file_name);
	return (1);
}

int	ft_words_counter_new(const char *s)
{
	int i;
	int word;

	if (!s || *s == '\0')
		return (0);
	i = 0;
	word = 0;
	if (s[0] != ' ' && s[0] != '\t')
		word++;
	while (s[i] != '\0')
	{
		if ((s[i] != ' ' && s[i] != '\t') && (s[i - 1] == ' ' || s[i - 1] == '\t'))
			word++;
		i++;
	}
	return (word);
}

char	*ft_one_word_new(const char *s, int *i)
{
	int		j;
	char	*temp;
	char	c;

	j = 0;
	while (s[j] != ' ' && s[j] != '\t' && s[j] != '\0')
		j++;
	c = s[j];
	j = 0;
	temp = (char *)malloc(sizeof(temp) * (ft_str_len_n(s, c)) + 1);
	while (s[*i] == c && s[*i] != '\0')
		*i += 1;
	while (s[*i] != c && s[*i])
	{
		temp[j] = s[*i];
		j++;
		*i += 1;
	}
	temp[j] = '\0';
	return (temp);
}

char	**ft_strsplit_new(char const *s)
{
	char	**fresh;
	int		i;
	int		j;
	int		wd;

	if (!s)
		return (NULL);
	wd = ft_words_counter_new(s);
	if (!(fresh = (char **)malloc(sizeof(char*) * wd + 1)))
		return (NULL);
	i = 0;
	while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
		i++;
	j = 0;
	while (s[i] != '\0' && j < wd)
	{
		fresh[j] = ft_one_word_new(s, &i);
		j++;
	}
	fresh[j] = NULL;
	return (fresh);
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
	printf("str =  %s\n", str);

	return (str);
}

void parse_string_save_data(char *line, t_all *champ)
{
	int		i;
	// char c;

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

		
		// return 0;
	
	// return 1;

	// while (l[i])
	// {
	// 	l[i]
	// }
}

void save_name(char *name, int fd, t_all *champ)
{
	char *line;
	// (void)fd;
	// char c;

	if (!save_file_name(name, champ))
		p_error("\nERROR! Wrong file extension: only *.s please.\n");
	while (get_next_line(fd, &line))
	{
		if (line[0] == '.')// && line[1] == 'n')//((ft_strstr(line, ".name")))
			parse_string_save_data(line, champ);
		if (!ft_strchr(line, '"') && line[0] != '#' && line[0] != ';')
			break ;
	}

}

int main(int argc, char **argv)
{
	t_all	*champ;
	int		fd;

	if (argc != 2)
		p_error("\n\tInvalid input arguments.\nPlease use the following structure:\n\t./asm champion_file.s\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		p_error("\nERROR! Not valid file.\n");
	champ = ft_memalloc(sizeof(t_all));
	save_name(argv[1], fd, champ);
	return 0;	
}