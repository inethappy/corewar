#include "../asm.h"
// ../vm_champs/asm ../vm_champs/champs/toto_test.s && xxd ../vm_champs/champs/toto_test.cor > ../asm/car.bt


int main(int argc, char **argv)
{
	t_all	*champ;
	int		fd;

	if (argc != 2)
		p_error("\n\tInvalid input arguments.\nPlease use the following structure:\n\t./asm champion_file.s\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		p_error("\nERROR! Not valid file.\n");
	champ = ft_memalloc(sizeof(t_all));
	champ->base = ft_memalloc(sizeof(headers_t));
	save_name(argv[1], fd, champ);
	save_inctructions(fd, champ);
	system("leaks asm > leaks.txt");
	return 0;	
}

// void parse_string_save_data(char *line, t_all *champ)
// {
// 	int i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		champ->byte_counter++;		

// 	}

// }

void check_save_label(char *line, t_all *champ)
{
	int colon;
	int i;
	// char *lbl;

	colon = 0;
	while(line[i])
	{
		if (!ft_strchr(LABEL_CHARS, line[i]) || colon > 1)
			p_error("\nERROR! Invalid label.\n") /// at string... ?
		if (ft_strchr(line, LABEL_CHAR))
			colon++;
		i++;
	}
	if (!champ->head)
		ft_lstnew

}

void	save_inctructions(int fd,t_all *champ)
{
	char *line;

	while (get_next_line(fd, &line))
	{
		if (ft_strchr(LABEL_CHARS, line[0]) && ft_strchr(line, LABEL_CHAR))
			check_save_label(line, champ);
		
			// if check_label(line);
			// 	parse_string_save_data(line, champ);
		
	}
}
