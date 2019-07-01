/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:42:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 13:43:15 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libft/includes/libft.h"
# include "op.h"

# define CODE_EXTENSION		".s"
# define BINARY_EXTENSION	".cor"

# define FLAG_DUMP64			(uint8_t)0b01000000
# define FLAG_DUMP32			(uint8_t)0b00100000
# define FLAG_AFF			(uint8_t)0b00010000

# define FLAG_VERBOSE		(uint8_t)0b00001111
# define FLAG_VERBOSE_8		(uint8_t)0b00001000
# define FLAG_VERBOSE_4		(uint8_t)0b00000100
# define FLAG_VERBOSE_2		(uint8_t)0b00000010
# define FLAG_VERBOSE_1		(uint8_t)0b00000001

# define ERR_PLAYERS_AMOUNT	"Invalid players' amount"
# define ERR_INIT_PLAYER	"Unable to initialise player"
# define ERR_INIT_CARRIAGE	"Unable to initialise carriage"
# define ERR_INIT_VM		"Unable to initialise virtual machine"
# define ERR_OPEN_BINARY	"Binary file cannot be opened"
# define ERR_READ_BINARY	"Binary file cannot be read"
# define ERR_INVALID_BINARY	"Invalid binary file"
# define ERR_INVALID_HEADER	"Invalid magic header"
# define ERR_NBR_PLAYER		"Invalid champion_number values"
# define ERR_NBR_DUBL		"Number dublication"

# define ERR_VERBOSE_ARG	"The argument after -v must be a positive digit"
# define ERR_DUMP_ARG		"The argument after -d must be a positive digit"
# define ERR_NBR_ARG		"The argument after -n must be a positive digit"

typedef struct s_game		t_game;
typedef struct s_champion	t_champion;
typedef struct s_carriage	t_carriage;
typedef struct s_operation	t_operation;

t_game						g_game;
uint8_t						g_flag;
uint32_t					g_id;

struct						s_game
{
	t_champion				*survivor;
	t_list					*players;
	int32_t					players_amount;
	t_list					*carriages;
	uint8_t					field[MEM_SIZE];
	int32_t					check_counter;
	int32_t					check_period;
	int32_t					check_amount;
	int32_t					cycle_counter;
	int32_t					live_counter;
	int32_t					dump_period;
	int32_t					dump_counter;
};

struct						s_champion
{
	int32_t					fd;
	t_header				*header;
	int						number;
	int						size;
	uint8_t					*code;
};

struct						s_operation
{
	char					*name;
	uint8_t					code;
	uint8_t					codage;
	uint8_t					dir_size;
	uint16_t				argc;
	int32_t					argv[3];
	uint8_t					argt[3];
	uint32_t				period;
	void					(*function)();
};

struct						s_carriage
{
	uint16_t				id;
	uint16_t				pos;
	uint16_t				live;
	uint8_t					carry;
	int32_t					reg[REG_NUMBER];
	t_operation				operation;
};

typedef struct				s_argument
{
	uint8_t					dump:2;
	uint8_t					a3:2;
	uint8_t					a2:2;
	uint8_t					a1:2;
}							t_arg;

typedef union				u_agrtype
{
	uint8_t					cell;
	t_arg					arg;
}							t_argtype;

typedef union				u_value
{
	uint32_t				word;
	uint8_t					byte[REG_SIZE];
}							t_value;

typedef enum				e_flag
{
	UNKNOWN,
	VERBOSE,
	DUMP32,
	DUMP64,
	AFF,
	CHAMPION_NUMBER
}							t_flag;

void						usage(void);
void						error(int trigger, char *msg);
int							is_number(char *str);
void						choose_num(t_list *lst);
void						sort_champions(void);
uint8_t						check_arg(uint32_t type, uint32_t arg);
int32_t						get_arg(t_carriage *carriage, uint32_t type,
												uint32_t arg, int32_t divider);
void						set_value(int32_t addr,
										uint32_t value, size_t size);
uint32_t					get_value(uint32_t addr, size_t size);
void						exec_function(t_list *lst);
void						log_field(void);
void						log_champion(t_list *lst);
void						log_winner(t_champion *champion);
uint8_t						check_arg(uint32_t type, uint32_t arg);
size_t						get_arglen(t_operation *operation);
void						get_argval(t_carriage *carriage);
int							new_champion(char *path, t_champion *champion);
t_champion					*game_loop(void);
void						get_argval(t_carriage *carriage);
size_t						get_arglen(t_operation *operation);
int							get_argtype(t_carriage *carriage);
int32_t						get_arg(t_carriage *carriage, uint32_t type,
												uint32_t arg, int32_t divider);
uint8_t						check_arg(uint32_t type, uint32_t arg);

#endif
