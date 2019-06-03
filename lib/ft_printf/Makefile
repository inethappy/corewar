NAME	=	libftprintf.a
OUTPUT	=	ft_printf.out
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SOURCES	=	ft_printf.c \
			flags.c \
			printing.c \
			print_numbers.c \
			help_functions.c \
			print_csp.c \
			print_float.c \
			handling.c \
			numbers_func.c
OBJECTS	=	$(SOURCES:.c=.o)

all:	$(NAME)

$(NAME):
	 $(CC) -c $(CFLAGS) -g $(SOURCES) ../libft/*.c -I ../libft/libft.h
	ar rc $(NAME) *.o
%.o: ./%.c
	gcc -o $@ -c $<
test:
	$(CC) -g -L. libftprintf.a $(SOURCES) main.c -o $(OUTPUT)
clean:
	rm -rf *.o
	rm -rf libft/*.o
fclean: clean
	rm -rf $(NAME)
re: fclean all
