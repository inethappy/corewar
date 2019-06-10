#include "../asm.h"
// ../vm_champs/asm ../vm_champs/champs/toto_test.s && xxd ../vm_champs/champs/toto_test.cor > ../asm/car.bt

void	check_arguments(t_list *all, t_token *cur, t_all *champ)
{
	int		i;
	t_token	*token;

	while (i++ < 16)
		if (ft_strequ(cur->name, op_tab[i].name))
			break ;
	all = all->next;
	while (all)
	{
		token = all->content;
		if (ft_strequ(op_tab[i].arg[1], "T_DIR") && token->type == 3)

		
	}
}

void	tokens_validation(t_list *all, t_all *champ)
{
	t_token	*cur;

	while (all)
	{
		cur = all->content;
		if (cur->type == 1)
			check_arguments(all, cur, champ);
		all = all->next;
	}
}

int		main(int argc, char **argv)
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
	tokens_validation(champ->head, champ);
	system("leaks asm > leaks.txt");
	return 0;	
}
