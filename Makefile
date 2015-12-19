NAME	= libuc.a

SRCS	= array_list.c \
	  linked_list.c \
	  btree.c
SRC 	= $(addprefix ./srcs/, $(SRCS))

CC = gcc

OBJ	= $(SRC:.c=.o)

INC 	= -I ./includes

FLAGS	= -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< $(INC)

clean: 
	rm -rf */*.o
	rm -rf */*.o.test

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all test clean