# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/20 13:01:19 by nsondag           #+#    #+#              #
#    Updated: 2020/10/28 13:46:36 by nsondag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC = gcc
FLAGS = -Wall -Werror -Wextra -O3
SRCS = srcs/
INCLS = includes/
LIB = libft/
HEADERS = md5.h
H = $(addprefix $(INCLS), $(HEADERS))
FILES = main.c md5_functions.c parse.c commands.c md5.c prepare_blocks.c \
		sha256_functions.c sha256.c shifts.c
OBJS = $(FILES:%.c=%.o)
	OBJS := $(addprefix $(SRCS), $(FILES:%.c=%.o))

RED=\033[0;91m
GREEN=\033[0;92m
NC=\033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) -L$(LIB) -lft
	@echo "$(GREEN)$(NAME) compiled$(NC)"

%.o: %.c $(H)
	@$(CC) $(FLAGS) -c -o $@ $< -I $(INCLS) -I $(LIB)$(INCLS)

clean:
	@make -C $(LIB) clean
	@rm -f $(OBJS)
	@echo "$(RED)$(NAME) cleaned$(NC)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB) fclean
	@echo "$(RED)$(NAME) fcleaned$(NC)"

re: fclean all
