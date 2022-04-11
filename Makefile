NAME = pipex

SRC = 	pipex.c pipex_end.c pipex_free.c str_utils.c split.c

OBJ = $(SRC: .c=.o)

CC = gcc
FLAGS = -Wall -Werror -Wextra

RM = rm -f -r

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -c $(OBJ) $(SRC)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)
	$(RM) *.dSYM

re: fclean all

.PHONY: all clean fclean re
