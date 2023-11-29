/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:28:06 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/29 00:00:45 by antoda-s         ###   ########.fr       */
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
# include "../include/error.h"
# include "../include/colors.h"
# include "../include/debug.h"

/* ************************************************************************** */
///	STRUCTS
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_EAT,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_NAME
}			t_token_type;

typedef struct s_line
{
	char	*line;
	char	**tokens_list;
	int		tokens_n;
	char	piped;
	char	parse_state;
}	t_line;

// typedef struct s_token
// {
// 	int				cmd_i;
// 	char			**cmd_full;

// 	struct s_token	*n;
// }					t_token;

/*********************************************/

typedef struct s_token
{
	char			*cmd;
	int				size;
	t_token_type	type;
	struct s_token	*next;
}				t_token;
/*********************************************/

typedef struct s_cmd
{
	struct s_token	*head;
	char			*line;
	int				pipes_q;
	int				pipe_i;
	int				redir_q;
	int				redir_i;
	int				redir_type;
	int				redir_fd1;
	int				redir_fd2;
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


/* ************************************************************************** */
///	parser.c
/* ************************************************************************** */

/// @brief 			Checks if the number of arguments is valid
/// @param argc		Number of arguments
/// @return			SUCCESS if valid, ERROR if invalid
int		invalid_argc(int argc);

/// @brief 			Checks if str has paired quotes and double quotes
/// @param str		String to parse
/// @param c		Character to check
/// @return
int		invalid_pair(char *str, char *c);

/// @brief 				Checks if the quotes are valid
/// @param cmdline		Command line
/// @return				SUCCESS if valid, ERROR if invalid
int		invalid_quotes(char *line);

/// @brief 			Checks if the argument is valid
/// @param argv		Argument
/// @return			SUCCESS if valid, ERROR if invalid
int		invalid_line(char *line);



/* ************************************************************************** */
///	error.c
/* ************************************************************************** */

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int		return_error(const char *msg, int system);



/* ************************************************************************** */
///	debug.c
/* ************************************************************************** */

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int		show_func(const char *func_name, int status);

/* ************************************************************************** */
///	trimmer.c
/* ************************************************************************** */

/// @brief 				Trims the token command from whitespaces
/// @param token		Token to be trimmed
/// @param trimmer		Trimmer characters
char	*trimmer(char *line, const char *trimmer);

/* ************************************************************************** */
///	xxxxx.c
/* ************************************************************************** */


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
