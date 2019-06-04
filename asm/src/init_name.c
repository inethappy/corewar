#include "../asm.h"

void	init_name(t_all *champ, char *line)
{
	char *buf;
	if (champ->base->prog_name[0] != '\0')
		p_error("\nERROR! Invalid command.\n");
	buf = save_command_data(line, 5);
	if (ft_strlen(buf) > PROG_NAME_LENGTH)
		p_error("\nERROR! Too long name. Max length = 128\n");		
	ft_strcpy(champ->base->prog_name, buf);
	free(buf);
}

void	init_comment(t_all *champ, char *line)
{
	char *buf;

	if (champ->base->comment[0] != '\0')
		p_error("\nERROR! Invalid command.\n");
	buf = save_command_data(line, 8);
	if (ft_strlen(buf) >  COMMENT_LENGTH)
		p_error("\nERROR! Too long comment. Max length = 2048\n");
	ft_strcpy(champ->base->comment, buf);
	free(buf);
}