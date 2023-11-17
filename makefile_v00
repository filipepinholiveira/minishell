
# path
LFT_PATH = SOURCES/LIBFT/


# links
LNK_LIBFT = $(LFT_PATH)libft.a

# rteste de alteracao de af
CFLAGS = -Wall -Wextra -Werror -pedantic # Use -pedantic if you want to strictly enforce the rules of the C standard.

MAND = SOURCES/minishell.c \
	SOURCES/ft_tokenize.c \
	SOURCES/ft_strtok.c \
	SOURCES/ft_execmd.c \
	SOURCES/ft_cd.c \
	SOURCES/pipelines.c \
	SOURCES/ft_get_location.c \
	# SOURCES/LIBFT/ft_strlcpy.c \
	# SOURCES/LIBFT/ft_strlen.c \
	# SOURCES/LIBFT/ft_strncmp.c \

# NAMES
LIBFT 		= libft.a
NAME = minishell

OBJ_MAND = $(MAND:.c=.o)

#Colors:
GRN		=	\e[38;5;118m
YLW		=	\e[38;5;226m
RED		=	\e[38;5;196m
BLU		=	\e[38:5:31m
WTH		=	\e[0m
CYN		:= \33[1;36m
RESET	:= \033[0m
BOLD	:= \033[1m

_INFO		=	[$(YLW)INFO$(WTH)]
_SUCCESS	=	[$(GRN)DONE$(WTH)]

all:$(NAME)

$(NAME): $(OBJ_MAND) $(LIBFT)
	@printf "$(RED)██$(WHT)"
	@cc $(OBJ_MAND) $(CFLAGS) -g $(LNK_LIBFT) -lreadline -o $(NAME)

# Rule to build object files from source files
%.o: %.c
# %.o: %.c
	@$(CC) $(CF) -c $< -o $@
	@printf "$(RED)██$(WHT)"

$(LIBFT):
	@printf "\n$(GRN)Generating Libft...$(WTH)\n"
	@make -C SOURCES/LIBFT/
	@printf "$(GRN)Libft created!$(WTH)\n\n"

clean:
	rm -f $(OBJ_MAND)

fclean: clean
	@make fclean -C $(LFT_PATH)
	rm -f $(NAME)

re: fclean all
#new comment

.PHONY: all clean fclean re