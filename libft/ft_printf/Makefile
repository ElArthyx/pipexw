# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 01:01:24 by alegrix           #+#    #+#              #
#    Updated: 2024/11/05 08:19:54 by alegrix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

OBJ = ft_printf.o\
	  ft_puthexai.o\
	  ft_putchari.o

${NAME} : ${OBJ}
	ar crs ${NAME} ${OBJ}

all: ${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f $(NAME)

re: fclean all
