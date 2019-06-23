#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../inc/libft.h"
# include "../inc/ft_printf.h"

typedef enum	s_types {label, op, reg, dir, indir, dir_l, indir_l} token_type;

typedef struct	s_token
{
	char		*name;
	char		arg_type;
	int			type;
	int			step;
}				t_token;

typedef struct	s_all
{
	char		*file_name;
	headers_t	*base;
	t_list		*head;
	t_list		*labels;
	int			byte_counter;
	int			tdir_size_cur;
	int			file_fd;
	int			line_counter;
	t_list		*code;
}				t_all;

typedef struct	s_op
{
	char		*name;
	int			arg_number;
	char		arg[3];
	int			code_op;
	int			cycle_to_do;
	char		*op_description;
	int			arg_size;
	int			tdir_size;
}				t_op;

t_op			op_tab[17];

// save name and comment
void			save_name(char *name, int fd, t_all *champ);
int				save_file_name(char *f_name, t_all *champ);
void			check_name_comment(int fd, char *line, t_all *champ);
char 			*save_command_data(int fd, char *line, int index, t_all *champ);
char			*find_string_tail(char *str, char *line, int fd, t_all *champ);
char			*save_end_of_command(char *buf, char *line, char *str);
int				check_tail(char *line);
void			init_name(int fd, t_all *champ, char *line);
void			init_comment(int fd, t_all *champ, char *line);

// additional functions
char			**ft_strsplit_new(char const *s);
char			*ft_one_word_new(const char *s, int *i);
int				ft_words_counter_new(const char *s);
t_list			*ft_lstnew_new(void *content, size_t content_size);
int				is_register(char *token);
void			add_list(t_list **list, void *ptr);
void			del_list(t_token *token, size_t content_size);

// save file
void			save_inctructions(int fd,t_all *champ);

void			parse_string_save_tokens(char **token, t_all *champ);
void			parse_string_save_tokens_split(char **token, t_all *champ);
int			 	check_separator(char **token, int i, t_all *champ);
int				detect_instruction(char *token, t_all *champ);
int				detect_label(char *token, int *label, t_all *champ);
int				wrong_line(char **token, int i, t_all *champ);

void			check_save_op(char *instr, t_all *champ);
void			check_save_label(char *line, t_all *champ);
void			check_save_instr(char **arg, t_all *champ);

void			set_instr_label(char *instr, t_all *champ, int i);
void			set_instr_nb(char *instr, t_all *champ);
void			set_instr_reg(char *arg, t_all *champ);

// arguments validation
void			tokens_validation(t_list *all, t_all *champ);
void			check_arguments(t_list *all, t_token *cur, t_all *champ);
void			is_correct_args(t_list *args, int op_nb, t_all *champ);
int				calculate_args(t_list *args);
void			is_existing_label(char *name, t_list *labels);
int				find_cur_operation(char *name);
void			save_args(t_list *args, int op_nb, t_all *champ, t_token *cur);
int				find_label(t_token *arg, t_list *lbls, t_token *cur);
void			save_args_code(t_list *args, t_all *champ);
void			del_args_list(t_list *args);

void			write_in_file(t_all *champ, t_list *code);
void			error_in_line(char *err, int line);


#endif
