# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 18:56:23 by chon              #+#    #+#              #
#    Updated: 2024/12/16 15:25:12 by honguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude 
LDFLAGS =
OS = $(shell uname)

ifeq (${OS}, Darwin)
	MLX_DIR = libs/mlx_macos
	LIBS = $(addprefix libs/, libft/libft.a mlx_macos/libmlx.a)
	LDFLAGS += -L/usr/lib -framework OpenGL -framework Appkit -lm
else ifeq (${OS}, Linux)
	MLX_DIR = libs/mlx_linux
	LIBS = $(addprefix libs/, libft/libft.a mlx_linux/libmlx.a)
	LDFLAGS += -L/usr/lib -lXext -lX11 -Ofast -lm
endif

LIBFT_DIR = libs/libft
INCL_DIR = include
SRC_FILES = main.c \
		$(addprefix parsing/, parse.c) \
		$(addprefix draw/, draw.c) \
		$(addprefix colors/, colors.c) \
		$(addprefix controls/, controls.c) \
		$(addprefix math/, point.c vector_1.c vector_2.c matrix_1.c matrix_2.c) \
		destroy/destroy.c
SRCS = $(addprefix src/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)
	
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