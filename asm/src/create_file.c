#include "../asm.h"

void hex_con(int32_t nbr, int size, t_all *champ)
{
	unsigned int tmp;
	int    i;
	unsigned int max;
	char   *res;

	if (size == 1)
		max = 255;
	if (size == 2)
		max = 65535;
	if (size == 4)
		max = 4294967295;
	if (nbr < 0)
		tmp = max + nbr + 1;
	else
		tmp = nbr;
	res = ft_memalloc(sizeof(char) * size);
	i = size;
	while (--i >= 0)
	{
		res[i] = tmp % 256;
		tmp /= 256;
	}
	write(champ->file_fd, res, size);
	free(res);
}

void write_in_file(t_all *champ)
{
	int8_t		i;

	(void)champ;
	i = 0;
	int size = 4;
	char *str = ft_strnew(PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	// while (size > 0)
	// {
	// 	str[0 + size - 1] = (uint8_t)((COREWAR_EXEC_MAGIC >> i) & 0xFF);
	// 	i += 8;
	// 	size--;
	// }
	size = 0;
	int tmp;
	while (size < 4)
	{
		tmp = COREWAR_EXEC_MAGIC;
		str[size] = (char)(tmp >> (24 - 8 * size));
		// str[0 + size - 1] = (uint8_t)((COREWAR_EXEC_MAGIC >> i) & 0xFF);
		// i += 8;
		size++;
	}
	write(champ->file_fd, str, 4);
	size = 0;

	while (size < 132)
	{
		write(champ->file_fd, champ->base->prog_name + size, 1);
		// champ->base->prog_name
		// str[0 + size - 1] = (uint8_t)((COREWAR_EXEC_MAGIC >> i) & 0xFF);
		// i += 8;
		size++;
	}
	size = 136;
	int j = 0;
	while (size < 2184)
	{
		write(champ->file_fd, champ->base->comment + j, 1);
		// champ->base->prog_name
		// str[0 + size - 1] = (uint8_t)((COREWAR_EXEC_MAGIC >> i) & 0xFF);
		// i += 8;
		size++;
		j++;
	}
	// write(champ->file_fd, &op_tab[10].code_op, 1);
	// t_list *l = champ->code;
	// int *g;


		int f = 0;
		// int d[5] = { 1, 3, 5, 6, 7};
		// while (f < 5)
		// {
		// 	write(champ->file_fd, &d[f], 1);
		// 	f++;
		// }
	while (champ->code)
	{

		// hex_con((int32_t)champ->code->content, champ->code->content_size, champ);
		f = champ->code->content_size;
		// while (f-- > 0)
		// write(champ->file_fd, &op_tab[0].code_op, 1);
		// rev_bytes(champ, champ->code->content_size, champ->code->content);

		while (f-- > 0)
			write(champ->file_fd, champ->code->content + f, 1);
		// write(champ->file_fd, &op_tab[0].code_op, 1);

		// int *g = champ->code->content;
		// int g2 = champ->code->content_size;
		// printf("YAYAYAYAYAY %x %d\n", *g, g2);
		champ->code = champ->code->next;
	}





	// char *o;
	// o = ft_strnew(4);
	// size = 0;
	// while (size < 4)
	// {
	// 	tmp = op_tab[10].code_op;
	// 	str[size] = (char)(tmp >> (24 - 8 * size));
	// 	// str[0 + size - 1] = (uint8_t)((COREWAR_EXEC_MAGIC >> i) & 0xFF);
	// 	// i += 8;
	// 	size++;
	// }
}



