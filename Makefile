# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chon <chon@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 08:55:08 by chon              #+#    #+#              #
#    Updated: 2025/02/03 16:06:57 by chon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
BONUS ?= 0
CFLAGS = -Wextra -Wall -Werror -g -fsanitize=address
INCLUDES = -Iinclude -I$(MLX_DIR) -Ilibs/libft

OS := $(shell uname)
CFLAGS += -DBONUS=$(BONUS)

Dar = Darwin
Lin = Linux

ifeq (${OS}, ${Dar})
MLX_DIR := libs/mlx_macos
MLX := mlx
LDFLAGS = -L$(MLX_DIR) -l$(MLX) -framework OpenGL -framework Appkit -Llibs/libft -lft -L/usr/lib -lm -fsanitize=address
else ifeq (${OS}, ${Lin})
MLX_DIR := libs/mlx_linux
MLX := mlx_Linux
LDFLAGS = -L$(MLX_DIR) -l$(MLX) -L/usr/lib -lXext -lX11 -lm -lz -Llibs/libft -lft -fsanitize=address
else
$(error Unsupported OS: $(OS))
endif

NAME := miniRT

SRC := main.c \
	$(addprefix colors/, colors_1.c colors_2.c frame.c paint.c) \
	$(addprefix parsing/, parse.c parse_ambient.c parse_light.c \
	parse_camera.c parse_sphere.c parse_utils.c parse_errors.c \
	parse_plane.c parse_cylinder.c parse_cube.c parse_cone.c \
	parse_extras.c parse_material.c parse_texture.c parse_xpm.c parse_pattern.c ft_atof.c) \
	$(addprefix destroy/, destroy.c errors.c) \
	$(addprefix threads/, init_join.c routines.c lerp_vertical.c lerp_horizontal.c) \
	$(addprefix raytracing/, lighting.c rays.c render.c) \
	$(addprefix hooks/, update.c keys.c mouse.c object.c camera_movement.c camera_rotations.c rodrigues.c) \
	$(addprefix math/, matrix_1.c matrix_2.c matrix_3.c matrix_4.c matrix_5.c matrix_6.c point.c vector_1.c \
	vector_2.c vector_3.c vector_4.c) \
	$(addprefix intersections/, world.c sphere.c plane.c cylinder.c cube.c cone.c) \
	$(addprefix textures/, bump_map.c pattern.c perlin_noise.c)
SRC_DIR := src
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

INC := colors.h common.h keys.h macros.h miniRT_math.h miniRT.h
LIBFT_DIR := libs/libft

INCLUDE := $(addprefix include/, $(INC))

OBJS := $(SRCS:.c=.o)

all: $(NAME)

bonus:
	$(MAKE) BONUS=1

mandatory:
	$(MAKE) BONUS=0

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(INCLUDE) $(SRCS)
	@make -C $(MLX_DIR)
	make -C libs/libft
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	@make -C $(MLX_DIR) clean
	make -C libs/libft clean
	rm -rf $(OBJS)

fclean:
	@make -C $(MLX_DIR) clean
	rm -rf $(MLX_DIR)/lib$(MLX).a
	make -C libs/libft fclean
	rm -rf $(OBJS)
	rm -rf $(NAME)

run: re $(NAME)
	rm -rf $(OBJS)
	@./$(NAME) ./scenes/complex.rt

brun:
	$(MAKE) BONUS=1
	rm -rf $(OBJS)
	@./$(NAME) ./scenes/complex.rt

leaks: $(NAME)
	@$(RM) $(OBJS)
	valgrind --leak-check=full ./$(NAME) ./scenes/complex.rt

bleaks: $(NAME)
	$(MAKE) BONUS=1
	@$(RM) $(OBJS)
	valgrind --leak-check=full ./$(NAME) ./scenes/complex.rt

re: fclean all

.PHONY: all clean fclean re bonus mandatory run brun leaks bleaks