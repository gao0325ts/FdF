NAME = lib.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = ./libft
GNL_DIR = ./get_next_line

SRCS = $(wildcard $(LIBFT_DIR)/*.c $(GNL_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
INCLUDES = ./includes

MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	ar rsc $@ $^

.c.o:
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
