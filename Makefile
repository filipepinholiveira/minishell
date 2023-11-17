# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 21:23:27 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/17 19:15:38 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name
NAME 		= minishell
# NAMEB 		= main_bonus
# libs and includes
LIBFT 		= libft.a
# LIBGFX 		= libgfx.a
# MLX 		= minilibx.a

LFT_PATH 	= ./libft/
# GFX_PATH 	= ./libgfx/
# MLX_PATH 	= ./minilibx-linux/

# includes dir
INCLUDES 	= ./include/

# sources and objects dirs
SRCDIR 	= srcs/
OBJDIR 	= build/
# SRCDIRB 	= srcsb/
# OBJDIRB 	= buildb/

# sources and objects base project
# FILES	=	main.c 				# Top level function
FILES 	=	minishell.c
FILES	+=	ft_tokenize.c
FILES	+=	ft_strtok.c
FILES	+=	ft_execmd.c
FILES	+=	ft_cd.c
FILES	+=	pipelines.c
FILES	+=	ft_get_location.c
# FILES	+=	add files names 1 file name per line # Describe function

# sources and objects bonus project
# FILESB	=	main_bonus.c
# FILESB	+=	fdf_bonus.c			# Top level fdf functions

SRC = $(addprefix $(SRCDIR), $(FILES))
OBJ = $(addprefix $(OBJDIR), $(FILES:.c=.o))

# SRCB = $(addprefix $(SRCDIRB), $(FILESB))
# OBJB = $(addprefix $(OBJDIRB), $(FILESB:.c=.o))

#compilation
CF 			= -Wall -Wextra -Werror -g
CC 			= cc
# MLX_CF 		= -lm -lX11 -lXext
I_HEADER	= -I include
# I_MLX 		= -I minilibx
I_LIBFT 	= -I libft
# I_GFX 		= -I libgfx
LNK_LIBFT 	= -L $(LFT_PATH) -lft
# LNK_MLX 	= -L $(MLX_PATH) -lmlx
# LNK_GFX 	= -L $(GFX_PATH) -lgfx

LEAKS 		= valgrind
LEAKS_FILE	= valgrind-log.txt
LF 			= --leak-check=full \
        		--show-leak-kinds=all \
        		--track-origins=yes \
        		--verbose \
        		--log-file=$(LEAKS_FILE) \
        		$(NAME) # args??

# common commands
RM 			= rm -f

#Colors:
GRN		=	\e[38;5;118m
YLW		=	\e[38;5;226m
RED		=	\e[38;5;196m
BLU		=	\e[38:5:31m
WTH		=	\e[0m
CYN		= \33[1;36m
RESET	= \033[0m
BOLD	= \033[1m

# messages
_INFO		=	[$(CYN)INFO$(WTH)]
_SUCCESS	=	[$(GRN)DONE$(WTH)]
_WARNING	=	[$(YLW)WARNING$(WTH)]
_ERROR		=	[$(RED)ERROR$(WTH)]

# rules
all: $(NAME)

# $(NAME): $(GFX) $(LIBFT) $(MLX) $(OBJ)
$(NAME): $(LIBFT) $(OBJ) | build
	@printf "$(GRN)Objects ready!$(WTH)\n\n"
	@printf "\n$(CYN)Generating $(NAME) executable...$(WTH)\n"
	@printf "$(RED)██$(WHT)"
#	$(CC) $(CF) $(OBJ) $(LNK_LIBFT) $(LNK_GFX) $(LNK_MLX) $(MLX_CF) -o $@
	@$(CC) $(CF) $(OBJ) $(LNK_LIBFT) -o $@
	@printf "$(GRN)Done!$(WTH)\n\n"

# $(NAMEB): $(GFX) $(LIBFT) $(MLX) $(OBJB)
# 	@printf "$(GRN)Objects ready!$(WTH)\n\n"
# 	@printf "\n$(CYN)Generating $(NAMEB) executable...$(WTH)\n"
# 	$(CC) $(CF) $(OBJB) $(LNK_LIBFT) $(LNK_GFX) $(LNK_MLX) $(MLX_CF) -o $@
# 	@printf "$(GRN)Done!$(WTH)\n\n"

build:
	@mkdir -p $(OBJDIR)
#	@mkdir -p $(OBJDIR)
	@printf "\n$(CYN)Compiling source files...$(WTH)\n"

# buildb:
# 	@mkdir -p $(OBJDIRB)
# 	@printf "\n$(CYN)Compiling source files...$(WTH)\n"

$(OBJDIR)%.o: $(SRCDIR)%.c | build
	$(CC) $(CF) -c $(I_LIBFT) $(I_HEADER) $< -o $@
	@printf "$(CYN)██$(WHT)"

$(LIBFT):
	@printf "\n$(GRN)Generating Libft...$(WTH)\n"
	@make -C $(LFT_PATH)
	@printf "$(GRN)Libft created!$(WTH)\n\n"

re: fclean all

# rebonus: fclean bonus

leaks:
	$(LEAKS) $(LF)
	@printf "$(GRN)Leaks log ready! Check valgrind-out.txt $(WTH)\n\n"

cleanleaks:
	$(RM) $(LEAKS_FILE)
	@printf "$(GRN)Leaks log file deleted.$(WTH)\n\n"

clean:
	@printf "\n$(YLW)Cleaning all object files from project...$(WTH)\n"
	$(RM) -rf $(OBJ) $(OBJDIR)
#	$(RM) -rf $(OBJB) $(OBJDIRB)

fclean: clean
	@printf "\n$(YLW)Cleaning all additional objects and libraries...$(WTH)\n"
	$(RM) -rf $(NAME)
#	$(RM) -rf $(NAMEB)
	@make fclean -C $(LFT_PATH)
#	@make fclean -C $(GFX_PATH)
#	@make clean -C $(MLX_PATH)
	@printf "$(GRN)All libraries removed!$(WTH)\n\n"
	make cleanleaks

# install:
# 	sudo apt-get install gcc make xorg libxext-dev libbsd-dev -y
# 	@printf "$(GRN)All dependencies ready!$(WTH)\n\n"

.PHONY: clean fclean re rebonus all bonus build

show:
	@echo ""
	@echo "$(YLW)[ALL PATHS 			*invoked with > make show* $(WTH)]"
	@echo ""
	@echo "$(GRN)██ LIBFT Directory $(WTH) :"
	@echo "$(LFT_PATH)$(WTH) $(WTH)"
	@echo ""
	@echo "$(GRN)██ LIBFT File $(WTH) :"
	@echo "$(WTH) $(LIBFT) $(WTH)"

	@echo ""
	@echo "$(RED)██ Sources directory :"
	@echo "$(BLU)./$(SRCDIR)$(WTH)"
	@echo ""
	@echo "$(RED)██ Sources files : $(WTH)"
	@echo "$(BLU)$(notdir $(FILES)) $(WTH)\n"
	@echo ""
	@echo "$(YLW)██ Executable file directory $(WTH) :"
	@echo "$(BLU)$(CURDIR) $(WTH)"
	@echo ""
	@echo "$(YLW)██ Executable file $(WTH) :"
	@echo "$(BLU)$(notdir $(NAME)) $(WTH)"
	@echo ""
	@echo "$(YLW)[GLOBAL OBJS DIR 	= $(WTH)$(BLU) $(OBJDIR)$(WTH) $(YLW)]$(WTH)"
	@echo "$(YLW)[MANDATORY OBJS FILE 	= $(WTH) $(notdir $(CYN)██ $(OBJ)) $(YLW)]$(WTH)"
	@echo ""

.SILENT: show
