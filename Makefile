# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chon <chon@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 18:56:23 by chon              #+#    #+#              #
#    Updated: 2025/01/22 15:33:54 by chon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
BONUS ?= 0
CFLAGS = -Wextra -Wall -Werror #-lz -Wno-unused-result -mavx -mavx2 -O3 -flto -funroll-loops -fno-signed-zeros #-g -fsanitize=address

OS := $(shell uname)
CFLAGS += -DBONUS=$(BONUS)

Dar = Darwin

Lin = Linux

ifeq (${OS}, ${Dar})
	BUILD_DIR := libs/mlx_macos
	MLX := mlx
	CFLAGS += -L$(BUILD_DIR) -I$(BUILD_DIR) -l$(MLX) -framework OpenGL -framework Appkit -Llibs/libft -Ilibs/libft -lft -L/usr/lib -lm
else ifeq (${OS}, ${Lin})
	BUILD_DIR := libs/mlx_linux
	MLX := mlx_Linux
	CFLAGS += -L$(BUILD_DIR) -I$(BUILD_DIR) -l$(MLX) -L/usr/lib -lXext -lX11 -lm -lz -Llibs/libft -Ilibs/libft -lft
else
	$(error Different OS!)
endif

NAME := miniRT

SRC := main.c \
			$(addprefix colors/, colors.c frame.c) \
			$(addprefix parsing/, parse.c parse_ambient.c parse_light.c \
				parse_camera.c parse_sphere.c parse_utils.c parse_errors.c \
				parse_plane.c parse_cylinder.c parse_cube.c parse_cone.c \
				parse_extras.c parse_material.c parse_texture.c parse_xpm.c ft_atof.c) \
			$(addprefix destroy/, destroy.c) \
			$(addprefix threads/, init_join.c routines.c lerp_vertical.c lerp_horizontal.c) \
			$(addprefix raytracing/, lighting.c pattern.c perlin_noise.c rays.c render.c) \
			$(addprefix hooks/, update.c keys.c mouse.c object.c camera_movement.c camera_rotations.c rodrigues.c) \
			$(addprefix math/, matrix_1.c matrix_2.c matrix_3.c matrix_4.c matrix_5.c matrix_6.c point.c vector_1.c vector_2.c vector_3.c) \
			$(addprefix intersections/, sphere.c plane.c cylinder.c world.c) \
			$(addprefix textures/, textures.c parametrizations.c tangents.c)
SRC_DIR :=	src
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

INC := miniRT.h miniRT_math.h common.h colors.h macros.h keys.h
INC_DIR := include
INCLUDE := $(addprefix $(INC_DIR)/, $(INC))

all: $(NAME)

bonus:
	$(MAKE) BONUS=1

mandatory:
	$(MAKE) BONUS=0

$(NAME): $(SRCS) $(INCLUDE)
	@make -C $(BUILD_DIR)
	make -C libs/libft
	$(CC) -o $(NAME) -I$(INC_DIR) $(SRCS) $(CFLAGS)

clean:
	@make -C $(BUILD_DIR) clean
	make -C libs/libft clean

fclean:
	@make -C $(BUILD_DIR) clean
	rm -rf $(BUILD_DIR)/lib$(MLX).a
	make -C libs/libft fclean
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

.PHONY: all clean fclean re
