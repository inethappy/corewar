#include "../asm.h"

void	write_magic_header(char *all_in, int input, t_all *champ)
{
	int tmp;
	int size;

	size = 0;
	while (size < 4)
	{
		tmp = input;
		all_in[size] = (char)(tmp >> (24 - 8 * size));
		size++;
	}
	write(champ->file_fd, all_in, 4);
}

void write_in_file(t_all *champ)
{
	char	*all_in;
	int		i;
	int		j;

	all_in = ft_strnew(PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	write_magic_header(all_in, COREWAR_EXEC_MAGIC, champ);
	i = -1;
	while (++i < 132)
		write(champ->file_fd, champ->base->prog_name + i, 1);
	if (champ->base->prog_size > 682)
		p_error("\nERROR! Very big executable code! Max = 682.\n");
	write_magic_header(all_in, champ->base->prog_size, champ);
	i = 139;
	j = -1;
	while (++i < 2192)
		write(champ->file_fd, champ->base->comment + ++j, 1);
	while (champ->code)
	{
		j = champ->code->content_size;
		while (j-- > 0)
			write(champ->file_fd, champ->code->content + j, 1);
		champ->code = champ->code->next;
	}
	printf("----------%d\n", champ->base->prog_size);
}
