# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/20 13:01:19 by nsondag           #+#    #+#              #
#    Updated: 2020/09/20 16:15:14 by nsondag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC = gcc
FLAGS = -Wall -Wextra -Werror -O3
SRCS = srcs/
INCLS = includes/
LIB = libft/
HEADERS = md5.h
H = $(addprefix $(INCLS), $(HEADERS))
FILES = main.c functions.c
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
