# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chon <chon@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 18:56:23 by chon              #+#    #+#              #
#    Updated: 2025/01/28 12:27:07 by chon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CC := cc
BONUS ?= 0
CFLAGS = -Wextra -Wall -Werror -Iinclude -g #-lz -Wno-unused-result -mavx -mavx2 -O3 -flto -funroll-loops -fno-signed-zeros # -fsanitize=address
LDFLAGS =

OS := $(shell uname)
CFLAGS += -DBONUS=$(BONUS)

Dar = Darwin

Lin = Linux

ifeq (${OS}, ${Dar})
	MLX_DIR = libs/mlx_macos
	LIBS = $(addprefix libs/, libft/libft.a mlx_macos/libmlx.a)
	LDFLAGS += -L/usr/lib -framework OpenGL -framework Appkit -lm
else ifeq (${OS}, ${Lin})
	MLX_DIR = libs/mlx_linux
	LIBS = $(addprefix libs/, libft/libft.a mlx_linux/libmlx.a)
	LDFLAGS += -L/usr/lib -lXext -lX11 -Ofast -lm
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

# INC := miniRT.h miniRT_math.h common.h colors.h macros.h keys.h
LIBFT_DIR := libs/libft
INC_DIR := include
# INCLUDE := $(addprefix $(INC_DIR)/, $(INC))

all: $(NAME)

bonus:
	$(MAKE) BONUS=1

mandatory:
	$(MAKE) BONUS=0

# $(NAME): $(SRCS) $(INCLUDE)
# 	@make -C $(BUILD_DIR)
# 	make -C libs/libft
# 	$(CC) -o $(NAME) -I$(INC_DIR) $(SRCS) $(CFLAGS)
OBJS := $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
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
