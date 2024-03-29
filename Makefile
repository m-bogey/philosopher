NAME = philo
CC = cc
SRC = main.c \
		utils.c \
		parsing.c \
		init_table.c \
		safe_functions.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c philo.h
	$(CC) -o $@ -c $<

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJ)

.PHONY: all clean fclean re