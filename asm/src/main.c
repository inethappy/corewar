#include "../asm.h"
// ../vm_champs/asm ../vm_champs/champs/toto_test.s && xxd ../vm_champs/champs/toto_test.cor > ../asm/car.bt

int calculate_args(t_list *args)
{
	int i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}

void check_args(t_list *args, int op_nb)
{
	int		count_args;
	t_token	*token;
	int		i;

	count_args = calculate_args(args);
	if (calculate_args(args) != op_tab[op_nb].arg_number)
		p_error("\nERROR! Wrong number of argument!\n");
	i = 0;
	while (args && i < op_tab[op_nb].arg_number)
	{
		token = args->content;
		if ((token->arg_type & op_tab[op_nb].arg[i]) == 0)
			p_error("\nERROR! Wrong argument in operation!\n");
		i++;
		args = args->next;
	}
}

void	check_arguments(t_list *all, t_token *cur, t_all *champ)
{
	int		i;
	t_token	*token;
	t_list	*args;

	args = NULL;
	(void)champ;
	i = -1;
	while (++i < 16)
		if (ft_strequ(cur->name, op_tab[i].name))
			break ;
	all = all->next;
	printf("YES\n");

	while (all)
	{
		token = all->content;
		// add_list(args, token);
		if (token->type == 0 || token->type == 1)
			break ;
		if (!args)
			args = ft_lstnew_new(token, sizeof(t_token));
		else
			ft_lstadd_end(args, ft_lstnew_new(token, sizeof(t_token)));
		// if (op_tab[i].arg[0] && ft_strstr(&op_tab[i].arg[0], "T_DIR") && token->type == 3)
		// 	printf("YES\n");
		
		printf("%s[%c][%d][%d]\n", token->name, op_tab[i].arg[0], op_tab[i].arg[1], op_tab[i].arg[2]);
		all = all->next;
	}
	check_args(args, i);
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
