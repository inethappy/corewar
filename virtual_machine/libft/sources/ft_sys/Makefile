include ../../src.mk

SRC_PATH	=	.
INC_PATH	=	../../includes
OBJ_PATH	=	../../objects

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

INC			=	-I $(INC_PATH)
OBJ			=	$(addprefix $(OBJ_PATH)/, $(SRC_SYS:.c=.o))

ft_sys: $(OBJ)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) $(INC) -o $@ -c $< $(FLAGS)
