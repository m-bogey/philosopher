NAME = philo

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES) #-fsanitize=thread

SRC_DIR = srcs

INCLUDES = includes

BUILD_DIR = .build

SRC_FILES = main.c \
		utils.c \
		parsing.c \
		init_table.c \
		safe_printf.c \
		dinner.c \
		gettime.c \
		getters_setters.c \
		synchro_utils.c \
		check_death.c

SRC = $(addprefix $(SRC_DIR)/, SRC_FILES)

OBJ = $(addprefix $(BUILD_DIR)/, $(SRC_FILES:.c=.o))

DEPS = $(OBJ:.o=.d)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) 

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJ) $(BUILD_DIR)

.PHONY: all clean fclean re
