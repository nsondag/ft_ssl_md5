# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/20 13:01:19 by nsondag           #+#    #+#              #
#    Updated: 2020/09/20 17:28:33 by nsondag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC = gcc
FLAGS = -O3
SRCS = srcs/
INCLS = includes/
LIB = libft/
HEADERS = md5.h
H = $(addprefix $(INCLS), $(HEADERS))
FILES = main.c functions.c parser.c commands.c init.c md5.c prepare_blocks.c \
				sha256_functions.c sha256.c
OBJS := $(addprefix $(SRCS), $(FILES:%.c=%.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $^ -L$(LIB) -lft

clean:
	@make -C $(LIB) clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB) fclean

re: fclean all
