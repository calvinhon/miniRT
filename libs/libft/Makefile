# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 17:16:25 by pabertha          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/12/19 11:51:05 by marvin           ###   ########.fr        #
=======
#    Updated: 2024/12/21 12:37:10 by honguyen         ###   ########.fr        #
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_printf.c \
	printf_c.c \
	printf_di.c \
	printf_p.c \
	printf_s.c \
	printf_u.c \
	printf_x.c \
	utils_blanks.c \
	utils_printf.c \
	utils_printfdi.c \
	utils_printfu.c \
	utils_sign.c \
	get_next_line.c \
	get_next_line_err.c \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c \
	get_next_line_utils.c

SRC_BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(OBJ_BONUS)
		ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)
<<<<<<< HEAD
		ranlib libft.a
=======
		
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec

%.o : %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@
	
clean :
	rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
