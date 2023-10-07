
#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../SOURCES/LIBFT/libft.h"

// ft_tokenize

//char *    ft_tokenize(char *input);
char *    ft_tokenize(const char *input, char **av, size_t *nbr_tokens);

// ft_strtok

char *ft_strtok(char *src_str, char *delim);

#endif