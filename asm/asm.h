#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../inc/libft.h"
# include "../inc/ft_printf.h"

typedef enum s_types {label, op, reg, dir, indir, dir_l, indir_l} token_type;

typedef struct  s_token
{
    char        *name;
    int         type;
    int         step;
}               t_token;

typedef struct  s_all
{
    char        *file_name;
    headers_t   *base;
    t_list     *head;
    int         byte_counter; 
    int         tdir_size;
}               t_all;

typedef struct  s_op
{
    char        *name;
    int         arg_number;
    char        arg[3];
    int         code_op;
    int         cycle_to_do;
    char        *op_description;
    int         byte;
    int         arg_size;
}               t_op;

t_op            oper[17];

// save name and comment
void            save_name(char *name, int fd, t_all *champ);
int             save_file_name(char *f_name, t_all *champ);
void            check_name_comment(char *line, t_all *champ);
char 	        *save_command_data(char *line, int index);
int             check_tail(char *line);
void            init_name(t_all *champ, char *line);
void            parse_string_save_data(char *line, t_all *champ);
void            init_comment(t_all *champ, char *line);


// additional functions
char            **ft_strsplit_new(char const *s);
char            *ft_one_word_new(const char *s, int *i);
int             ft_words_counter_new(const char *s);

// save file
void            save_inctructions(int fd,t_all *champ);

#endif