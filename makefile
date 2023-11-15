# rteste de alteracao de af
CFLAGS = -Wall -Wextra -Werror -pedantic # Use -pedantic if you want to strictly enforce the rules of the C standard.

MAND = SOURCES/minishell.c \
	SOURCES/ft_tokenize.c \
	SOURCES/ft_strtok.c \
	SOURCES/ft_execmd.c \
	SOURCES/ft_cd.c \
	SOURCES/pipelines.c \
	SOURCES/ft_get_location.c \
	SOURCES/LIBFT/ft_strlcpy.c \
	SOURCES/LIBFT/ft_strlen.c \
	SOURCES/LIBFT/ft_strncmp.c \

NAME = minishell
OBJ_MAND = $(MAND:.c=.o)

all:$(NAME)

$(NAME):$(OBJ_MAND)
	cc $(OBJ_MAND) $(CFLAGS) -g -lreadline -o $(NAME)

clean:
	rm -f $(OBJ_MAND)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re