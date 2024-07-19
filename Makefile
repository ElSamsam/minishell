# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 01:12:35 by saperrie          #+#    #+#              #
#    Updated: 2024/07/18 01:10:23 by saperrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

INCLUDE_DIR = header/
LIBFT_DIR = libft_improved/

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)
DFLAGS = -MMD -MP
LFLAGS = -L$(LIBFT_DIR) -lft -lreadline

OBJECT_DIR = .obj/

OBJECTS = $(patsubst src/%.c,$(OBJECT_DIR)%.o,\
		  src/main.c \
		  src/big_parse.c \
		  src/lexing.c \
		  src/expansion.c \
		  src/parsing.c \
		  src/utils/clean_quotes.c \
		  src/utils/utils.c \
		  src/utils/expand_utils.c \
		  src/utils/redirection_utils.c \
		  src/utils/super_expand.c \
		  src/utils/parsing_utils.c \
		  )

DEPENDENCIES = $(OBJECTS:.o=.d)

LIBFT = $(LIBFT_DIR)libft.a
NAME = minishell

.PHONY: all
all: $(NAME)

-include $(DEPENDENCIES)

$(NAME): $(OBJECTS) | $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ $(OBJECTS) $(LFLAGS)

$(OBJECT_DIR)%.o: src/%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir -p $@
	mkdir -p $@utils/

$(LIBFT)::
	@make --no-print-directory -C $(LIBFT_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean
	@make --no-print-directory all
