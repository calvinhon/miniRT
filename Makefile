# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chon <chon@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 18:56:23 by chon              #+#    #+#              #
#    Updated: 2024/11/21 18:57:27 by chon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CFLAGS = -Wall -Wextra -Werror -Iinclude -L/usr/lib
OS = $(shell uname)

ifeq (${OS}, Darwin)
	MLX_DIR = libs/mlx_macos
	LIBS = $(addprefix libs/, libft/libft.a mlx_macos/libmlx.a)
	CFLAGS += -framework OpenGL -framework Appkit -lm
else ifeq (${OS}, Linux)
	MLX_DIR = libs/mlx_linux
	LIBS = $(addprefix libs/, libft/libft.a mlx_linux/libmlx.a)
	CFLAGS += -lXext -lX11 -Ofast -lm
endif

LIBFT_DIR = libs/libft
INCL_DIR = include
SRC_FILES = main.c \
		$(addprefix parsing/, parse.c) \
		$(addprefix colors/, colors.c) \
		$(addprefix controls/, controls.c) \
		$(addprefix math/, point.c vector_1.c vector_2.c)
SRCS = $(addprefix src/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(LIBS) $(OBJS) -o $(NAME) 

all: $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.phony: all clean fclean re