NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC_DIR = ./srcs
LIB_DIR = ./lib
MLX_DIR = ./minilibx-linux

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
INCLUDES = -I ./includes -I ./$(MLX_DIR) -I ./$(LIB_DIR)/includes

LIB = lib.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIB_DIR)/$(LIB) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB_DIR)/$(LIB)

re: fclean all

.PHONY: all clean fclean re