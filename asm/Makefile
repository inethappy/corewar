NAME		:=	asm
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror

SOURCES_DIR	:= ./src/
OBJECTS_DIR	:= ./obj/
LIB_DIR		:= ../lib/
SOURCES		:=	main.c \
				split_string_with_space_and_tabs.c \
				op.c \
				save_name.c \
				init_name.c \
				additional_functions.c \
				save_instructions.c	\
				parse_tokens.c \
				check_tokens.c \
				tokens_validation.c \
				args_validation.c \
				create_file.c \
				detection_tokens.c

OBJECTS		:= $(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	:= $(LIB_DIR)libft
LIBFT_INC	:= $(LIBFT_DIR)
LIBFT_FL	:= -lft -L $(LIBFT_DIR)

PRINTF		:= $(PRINTF_DIR)libftprintf.a
PRINTF_DIR	:= $(LIB_DIR)ft_printf
PRINTF_INC	:= $(PRINTF_DIR)
PRINTF_FL	:= $(PRINTF_DIR)/libftprintf.a

LIB_FLAGS	:= $(LIBFT_FL) $(PRINTF_FL)

HEADER_FLAGS	:= -I asm.h -I $(LIBFT_INC) -I $(PRINTF_INC)

all:	$(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) $(LIB_FLAGS) -o $(NAME)

$(OBJECTS): | $(OBJECTS_DIR)

$(OBJECTS_DIR):
		mkdir $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(HEADER_FLAGS)

$(PRINTF):
		make -C $(PRINTF_DIR)

$(LIBFT):
		make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJECTS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJECTS_DIR)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)

re: fclean all

vpath %.c $(SOURCES_DIR)
