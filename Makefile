# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/30 12:56:32 by vkryvono          #+#    #+#              #
#    Updated: 2019/06/30 13:10:36 by vkryvono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

ASM_NAME	=	asm
VM_NAME		=	corewar

ASM_PATH	=	./assembler/
VM_PATH		=	./virtual_machine/

all: $(ASM_NAME) $(VM_NAME)

$(ASM_NAME):
	make -C $(ASM_PATH)
	mv $(ASM_PATH)/$(ASM_NAME) .

$(VM_NAME):
	make -C $(VM_PATH)
	mv $(VM_PATH)/$(VM_NAME) .

clean:
	make -C $(ASM_PATH) clean
	make -C $(VM_PATH) clean

fclean: clean
	rm -rf $(ASM_NAME) $(VM_NAME)
	make -C $(ASM_PATH) fclean
	make -C $(VM_PATH) fclean

re: fclean all
