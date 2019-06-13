#include "../asm.h"

void write_in_file(t_all *champ)
{
	int8_t		i;

	(void)champ;
	i = 0;
	int size = 4;
	char *str = ft_strnew(PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	while (size > 0)
	{
		// char c = str[i];
		// write(champ->file_fd, &c, 1);
		// str[i] = (char)(COREWAR_EXEC_MAGIC >> (24 - 8 * i));
				str[0 + size - 1] = (uint8_t)((COREWAR_EXEC_MAGIC >> i) & 0xFF);

		i += 8;
		size--;
	}
		write(champ->file_fd, str, PROG_NAME_LENGTH);

}
