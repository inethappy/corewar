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
    // char *file_name;
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

// t_op				g_tab[17];

int             save_file_name(char *f_name, t_all *champ);


#endif