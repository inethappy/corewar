include ../../src.mk

SRC_PATH	=	src
INC_PATH	=	../../includes
OBJ_PATH	=	../../objects

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

INC			=	-I $(INC_PATH)
OBJ			=	$(addprefix $(OBJ_PATH)/, $(SRC_PRINTF:.c=.o))

ft_printf: $(OBJ)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) $(INC) -o $@ -c $< $(FLAGS)
