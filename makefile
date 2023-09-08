CFLAGS = -Wall -Wextra -Werror -pedantic # Use -pedantic if you want to strictly enforce the rules of the C standard.

MAND = SOURCES/minishell.c \
	SOURCES/ft_tokenize.c \
	SOURCES/LIBFT/ft_strlcpy.c \
	SOURCES/LIBFT/ft_strlen.c \

NAME = minishell
OBJ_MAND = $(MAND:.c=.o)

all:$(NAME)

$(NAME):$(OBJ_MAND)
	cc $(OBJ_MAND) $(CFLAGS) -g -o $(NAME)

clean:
	rm -f $(OBJ_MAND)

fclean: clean
	rm -f $(NAME)

re: fclean all