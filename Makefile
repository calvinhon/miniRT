# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 18:56:23 by chon              #+#    #+#              #
#    Updated: 2024/12/16 14:59:59 by chon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CFLAGS = -Wall -Wextra -Werror -Iinclude -g -fsanitize=address
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

# $(addprefix parsing/, parse.c new_minirt.c parsa_data.c read_file.c) \

LIBFT_DIR = libs/libft
INCL_DIR = include
SRC_FILES = main.c \
		$(addprefix draw/, draw.c) \
		$(addprefix colors/, colors.c) \
		$(addprefix controls/, controls.c) \
		$(addprefix math_c/, point.c vector_1.c vector_2.c vector_3.c \
			matrix_1.c matrix_2.c matrix_3.c matrix_4.c matrix_5.c matrix_6.c) \
		$(addprefix lighting_and_shading/, lighting.c normal_at.c) \
		$(addprefix intersections_c/, world.c sphere.c) \
		$(addprefix raytracing_c/, rays.c render.c) \
		camera_c/camera.c \
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