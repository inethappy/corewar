include src.mk

.PHONY: all clean fclean re

NAME		=	libft.a

INC_PATH	=	./includes
SRC_PATH	=	./sources
OBJ_PATH	=	./objects

OBJ_MEMORY	=	$(addprefix $(OBJ_PATH)/, $(SRC_MEMORY:.c=.o))
OBJ_STRING	=	$(addprefix $(OBJ_PATH)/, $(SRC_STRING:.c=.o))
OBJ_PRINTF	=	$(addprefix $(OBJ_PATH)/, $(SRC_PRINTF:.c=.o))
OBJ_LIST	=	$(addprefix $(OBJ_PATH)/, $(SRC_LIST:.c=.o))
OBJ_SYS     =	$(addprefix $(OBJ_PATH)/, $(SRC_SYS:.c=.o))

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
INC			=	-I $(INC_PATH)

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ_MEMORY) $(OBJ_STRING) $(OBJ_LIST) $(OBJ_PRINTF) $(OBJ_SYS)
	ar rc $(NAME) $(OBJ_MEMORY) $(OBJ_STRING) $(OBJ_LIST) $(OBJ_PRINTF) $(OBJ_SYS)
	ranlib $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_MEMORY):
	make -C $(DIR_MEMORY)

$(OBJ_STRING):
	make -C $(DIR_STRING)

$(OBJ_PRINTF):
	make -C $(DIR_PRINTF)

$(OBJ_LIST):
	make -C $(DIR_LIST)

$(OBJ_SYS):
	make -C $(DIR_SYS)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
