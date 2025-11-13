# ----------------------------
# VARIABLES
# ----------------------------
NAME = move
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux
LDFLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm
SRC = main.c utils.c
OBJ = $(SRC:.c=.o)

# ----------------------------
# RULES
# ----------------------------
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
