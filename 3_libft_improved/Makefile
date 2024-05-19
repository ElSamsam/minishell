# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 20:39:49 by saperrie          #+#    #+#              #
#    Updated: 2024/04/03 16:40:34 by saperrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRC_DIR		=	src/

SRCS_BONUS	=	

SRCS		=	$(addprefix $(SRC_DIR), \
				ft_isalpha.c \
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
				get_next_line.c \
				get_next_line_utils.c \
				ft_printf.c \
				ft_printf_utils.c \
				putchar_sz.c \
				putstr_sz.c \
				putnbr_base.c \
				u_putnbr_base.c \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c)


OBJ_DIR		=	.obj/


OBJS		=	$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)


CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror
IFLAGS	=	-I./


all					:	$(NAME)


$(NAME)				:	$(OBJS)
	ar rc $(NAME) $(OBJS)


$(OBJ_DIR)			:
	mkdir $@


$(OBJ_DIR)%.o		:	$(SRC_DIR)%.c libft.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@



clean				:
	rm -rf $(OBJ_DIR)


fclean				: clean
	rm -f libft.a


re					:	fclean
	@make --no-print-directory all


.PHONY				:	all clean fclean re
