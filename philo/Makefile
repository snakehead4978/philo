NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 
# CFLAGS += -fsanitize=thread

INC = -I./includes

DIR_SRC = srcs/

SRC = misc.c philo.c threader.c libs.c

MAIN = main.c

OBJ_SRC = $(addprefix $(DIR_SRC), $(SRC:.c=.o))

OBJ_MAIN = $(MAIN:.c=.o)

OBJ_ALL = $(OBJ_SRC) $(OBJ_MAIN)

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJ_ALL)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

clean:
	rm -rf $(OBJ_ALL)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re