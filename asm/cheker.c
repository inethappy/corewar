#include "../inc/libft.h"
#include <stdio.h>

// gcc -lft -L ../lib/libft cheker.c -o cheker.o
// ../cheker.o file.my file.or

// ./asm ../vm_champs/champs/42.s && xxd 42.cor > file.my && ../vm_champs/asm ../vm_champs/champs/42.s && xxd ../vm_champs/champs/42.cor > file.or
// jumper
int main(int argc, char **argv)
{
	int fd1;
	int fd2;

	if ((fd1 = open(argv[1], O_RDONLY)) < 0)
		p_error("\nERROR! Not valid file.\n");
	if ((fd2 = open(argv[2], O_RDONLY)) < 0)
		p_error("\nERROR! Not valid file.\n");
	char *str1;
	char *str2;
	// printf("$^$^\n");
	while (get_next_line(fd1, &str1) && get_next_line(fd2, &str2))
	{
		printf("%s			%s\n", str1, str2);
		if (ft_strcmp(str1, str2))
			p_error("\nERROR! \n");
	}
	return 0;
}
