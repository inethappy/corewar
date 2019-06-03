#include "../asm.h"
// ./vm_champs/asm ./vm_champs/champs/toto_test.s && xxd ./vm_champs/champs/toto_test.cor > ./asm/car.bt


int main(int argc, char **argv)
{
	t_all	*champ;
	int		fd;

	if (argc != 2)
		p_error("\n\tInvalid input arguments.\n
		Please use the following structure:\n\t./asm champion_file.s\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		p_error("\nERROR! Not valid file.\n");
	champ = ft_memalloc(sizeof(t_all));
	save_name(argv[1], fd, champ);
	save_inctructions(fd, champ);
	system("leaks asm > leaks.txt");
	return 0;	
}

void	save_inctructions(int fd,t_all *champ)
{
	char *line;

	while (get_next_line(fd, &line))
	{
		
		
	}
}
