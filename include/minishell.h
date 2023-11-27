/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:28:06 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/27 17:17:56 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

/* ************************************************************************** */
///	STRUCTS
/* ************************************************************************** */
typedef struct s_line
{
	char	*line;
	char	**tokens_list;
	int		tokens_n;
	char	piped;
	char	parse_state;
}	t_line;

typedef struct s_token
{
	int				cmd_i;
	char			**cmd_full;
	struct s_token	*n;
	struct s_token	*p;
}					t_token;

typedef struct s_cmd
{
	struct s_token	*head;
	char			*line;
	int				pipes_q;
}					t_cmd;

# ifndef CPIPE
#  define CPIPE 11
# endif
# ifndef INWORD
#  define INWORD 12
# endif

# ifndef OUTWORD
#  define OUTWORD 13
# endif

# ifndef INQUOTE
#  define INQUOTE 14
# endif



// ft_tokenize

//char *    ft_tokenize(char *input);
char	*ft_tokenize(const char *input, size_t *nbr_tokens);

// ft_strtok

char	*ft_strtok(char *src_str, char *delim);

//ft_execmd.c
void	ft_execmd(char **Token_list, int tokens_nbr);

//get_location.c

char	*get_location(char *command);

//ft_cd.c
int		cd_command(char **args);

#endif
