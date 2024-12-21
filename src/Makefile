# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 18:56:23 by chon              #+#    #+#              #
#    Updated: 2024/12/21 14:37:51 by honguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_parse
CC = cc
CFLAGS = -Wall -Wextra -Werror -I ../include 

BONUS ?= 0

# Append bonus flag to CFLAGS
CFLAGS += -DBONUS=$(BONUS)

LDFLAGS =
OS = $(shell uname)

ifeq (${OS}, Darwin)
	MLX_DIR = ../libs/mlx_macos
	LIBS = $(addprefix ../libs/, libft/libft.a mlx_macos/libmlx.a)
	LDFLAGS += -L${MLX_DIR} -framework OpenGL -framework Appkit -lm
else ifeq (${OS}, Linux)
	MLX_DIR = ../libs/mlx_linux
	LIBS = $(addprefix ../libs/, libft/libft.a mlx_linux/libmlx.a)
	LDFLAGS += -L${MLX_DIR} -lXext -lX11 -Ofast -lm
endif

LIBFT_DIR = ../libs/libft
INCL_DIR = ../include
SRC_FILES = main_h.c \
		$(addprefix parsing/, 0errors.c 1check_filename.c 2new_minirt.c 3parse.c \
		31read_file.c 32parse_data.c 321parse_utils.c 322parse_objects.c 322parse_objects2.c ft_atof.c)
SRCS = $(addprefix ./, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)

all: $(NAME)

bonus:
	$(MAKE) BONUS=1

mandatory:
	$(MAKE) BONUS=0

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

run: $(NAME)
	rm -rf $(OBJS)
	@./$(NAME) ../scenes/mandatory/temple.rt

brun:
	$(MAKE) BONUS=1
	rm -rf $(OBJS)
	@./$(NAME) ../scenes/bonus/temple.rt

leaks: $(NAME)
	@$(RM) $(OBJS)
	valgrind --leak-check=full ./$(NAME) ../scenes/bonus/temple.rt

bleaks: $(NAME)
	$(MAKE) BONUS=1
	@$(RM) $(OBJS)
	valgrind --leak-check=full ./$(NAME) ../scenes/bonus/temple.rt

.phony: all clean fclean re