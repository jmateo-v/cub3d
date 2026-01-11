CC      = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(MLX_DIR)/include -I$(MLX_DIR)/include/MLX42 -I$(LIBFT_DIR)

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -lglfw -ldl -pthread -lm -DDEBUG=1

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRC = src/main.c\
	src/init/init_game.c\
	src/input/init_hooks.c\
	src/input/key_handler.c\
	src/input/game_loop.c\
	src/input/movement.c\
	src/input/rotation.c\
	src/render/render_frame.c\
	src/render/raycaster/raycaster.c\
	src/render/raycaster/ray_single.c\
	src/render/raycaster/ray_dir.c\
	src/render/raycaster/ray_delta.c\
	src/render/raycaster/ray_step_and_side.c\
	src/render/raycaster/ray_DDA.c\
	src/render/raycaster/ray_wall.c\
	src/render/raycaster/ray_draw.c\
	src/utils/error_handler.c\
	src/utils/sec_utils.c\
	src/utils/cleanup.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = cub3d

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LIB) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re