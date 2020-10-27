# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsondag <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/14 21:09:08 by nsondag           #+#    #+#              #
#    Updated: 2020/10/27 13:41:17 by nsondag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c\
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c\
		ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c\
		ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c\
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c\
		ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c\
		ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c\
		ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c\
		ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c\
		ft_toupper.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c\
		ft_lstiter.c ft_lstmap.c\

BONUS = ft_next_sqrt.c ft_sqrt.c ft_atoi_base.c ft_issorted.c\
		ft_isrevsorted.c word_count.c ft_pow.c ft_strtoupper.c

FT_PRINTF = converse_c.c converse_d.c converse_percent.c converse_s.c\
			converse_u.c converse_ws.c ft_lltoa_base.c ft_llutoa_base.c\
			ft_printf.c handle.c modifier.c parser.c sp_strlen.c u_count.c\
			count.c

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

INCL = libft.h ft_printf.h

OBJ := $(SRC:%.c=%.o)

OBJB := $(BONUS:%.c=%.o)

OBJPF := $(FT_PRINTF:%.c=%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	@gcc -c $(FLAGS) $(SRC) $(BONUS) $(FT_PRINTF)
	@ar rc $(NAME) $(OBJ) $(OBJB) $(OBJPF)
	@ranlib libft.a

clean:
	@/bin/rm -f $(OBJ) $(OBJB) $(OBJPF)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
