# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/30 13:16:04 by vkryvono          #+#    #+#              #
#    Updated: 2019/06/30 13:40:11 by vkryvono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar

CC			=	gcc

FLAGS		=	-Wall -Werror -Wextra

INC_PATH	=	./includes
OBJ_PATH	=	./objects
SRC_PATH	=	./sources

INC			=	-I./includes/\
				-I./libft/includes/libft.h

SRC			=	alert.c\
				arguments.c\
				func_fork.c\
				func_ld.c\
				func_math.c\
				func_misc.c\
				func_st.c\
				functions.c\
				game.c\
				init_champion.c\
				logger.c\
				main.c\
				utilities.c

OBJ = $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))

LIBFT	=		-L./libft/ -lft

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) $(INC) -o $@ -c $< $(FLAGS)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) -o $(NAME) $(OBJ) $(LIBFT)
	
clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
