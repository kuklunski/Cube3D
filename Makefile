NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./libft -I./ft_printf -I/usr/local/include
LDFLAGS = -L./libft -lft \
		  -L./ft_printf -lftprintf \
		  -lmlx -lXext -lX11 -lm

SRC = main.c \
	  raycasting/init_data.c \
	  raycasting/init_dirplane.c \
	  raycasting/handle_key.c \
	  raycasting/raycasting_algo.c \
	  raycasting/raycasting_algo2.c \
	  raycasting/utils.c \
	  raycasting/init_textures.c \
	  src/check_xpm_extension.c \
	  src/extract_map_utils.c \
	  src/floor_ceiling_range_check.c \
	  src/texture_checks.c \
	  src/handle_errors.c \
	  src/init_reset_data.c \
	  src/free_after_parsing.c \
	  src/flood_fill_map.c \
	  src/map_validation.c \
	  src/extract_map.c \
	  src/premap_element_checks.c \
	  src/extract_floor_and_ceiling.c \
	  src/extract_floor_and_ceiling_utils.c \
	  src/extract_textures.c \
	  src/get_number_of_lines.c \
	  src/file_checking.c \
	  src/get_file_data.c \
	  gnl/get_next_line.c \
	  gnl/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = libft.a
FT_PRINTF_DIR = ft_printf
FT_PRINTF = libftprintf.a

# **************************************************************************** #
#                                RULES                                         #
# **************************************************************************** #

all: $(LIBFT) $(FT_PRINTF) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
