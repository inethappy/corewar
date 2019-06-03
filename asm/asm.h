#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../inc/libft.h"
# include "../inc/ft_printf.h"

typedef struct  s_all
{
    char    *file_name;
    char *name;
    char *comment;
    int fd;
}               t_all;

typedef struct  s_op
{
    char    *name;
    int     arg_number;
    char    arg[3];
    int     code_op;
    int     cycle_to_do;
    char    *op_description;
    int     byte;
    int     arg_size;
}               t_op;

// save name and comment
void            save_name(char *name, int fd, t_all *champ);
int             save_file_name(char *f_name, t_all *champ);
void            parse_string_save_data(char *line, t_all *champ);
char            *save_command_data(char *line, int index);
int             check_tail(char *line);

// additional functions
char            **ft_strsplit_new(char const *s);
char            *ft_one_word_new(const char *s, int *i);
int             ft_words_counter_new(const char *s);


#endif