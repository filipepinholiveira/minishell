
#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../SOURCES/LIBFT/libft.h"

// ft_tokenize
char *    ft_tokenize(char *input, char **av);

#endif