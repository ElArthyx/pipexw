NAME = pipex

SOURCES =    src/pipex.c \
            src/utils.c \

INCLUDE = -I SOURCES -I libft -I ft_printf

LIBFTPATH = libft
LIBFT = $(LIBFTPATH)/libft.a
PRINTF_P = libft/ft_printf
FT_PRINTF = $(PRINTF_P)/libftprintf.a

OBJECTS = $(SOURCES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)
all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(FT_PRINTF)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean r
