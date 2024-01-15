/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:28:06 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/15 10:56:16 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../include/error.h"
# include "../include/colors.h"
# include "../include/debug.h"

# define MAX_PATH_LEN 4096

extern int	g_exit_status;

/* ************************************************************************** */
///	STRUCTS
/* ************************************************************************** */

/// @brief 				Enum to hold the token types
/// @param TK_WS		Empty token
/// @param TK_PIPE	Pipe token
/// @param TK_R_IN	Redirection input token
/// @param TK_R_OUT	Redirection output token
/// @param TK_NAME	Name token
typedef enum e_token_type
{
	TK_WS,
	TK_PIPE,
	TK_R_IN,
	TK_R_OUT,
	TK_NAME,
	TK_EQUAL
}			t_token_type;

typedef enum e_cmd_type
{
	CMD_EXEC,
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT
}			t_cmd_type;

/// @brief 				Struct to hold the token variables (see t_token_type)
/// @param op			Token char set
/// @param size			Token char set length
/// @param type			Token type (as per enum t_token_type)
typedef struct s_operations
{
	const char		*op;
	int				size;
	t_token_type	type;
}				t_ops;

/// @brief 				Struct to hold the token variables
/// @param content		Token content
/// @param size			Token size
/// @param type			Token type
/// @param next			Next token
typedef struct s_token
{
	char			*content;
	int				size;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

/// @brief 				Struct to hold the builtin command variables
/// @param bi_cmd		Builtin command
/// @param bi_func		Builtin function
/// @param va_args		Variable arguments
typedef struct s_bi_cmd
{
	const char		*bi_cmd;
	const void		*bi_func;
	void			*script;
	int				n;
}				t_bi_cmd;

typedef struct s_redirection
{
	char	*name;
	int		flag;
	t_list	*heredoc;
}				t_redirection;

/// @brief 				Struct to hold the command variables
/// @param cmd			Command itself
/// @param argc			Number of arguments
/// @param argv			Arguments
/// @param out			Redirection output content
/// @param in			Redirection input content
typedef struct s_command
{
	char			*cmd;
	int				argc;
	char			**argv;
	t_redirection	out;
	t_redirection	in;
}				t_command;

/// @brief 				Struct to hold the minishell variables
/// @param commands		Commands to be executed
/// @param cmd_count	Number of commands
/// @param exit_status	Exit status
/// @param envp			Environment variables
/// @param termios_p	Terminal settings
typedef struct s_script
{
	t_command		*commands;
	int				cmd_count;
	int				exit_status;
	char			**envp;
	char			**envt;
	struct termios	termios_p;
}				t_script;

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
///	main.c
/* ************************************************************************** */

/// @brief 		Creates array from system environment variables
/// @param envp system environment variables from main (... char **envp)
/// @return 	array copy of system environment variables
char	**envp_getter(char **envp);

/// @brief 				Gets the terminal settings
/// @param termios_p	Pointer to the termios settings structure
void	termios_getter(struct termios *termios_p);

/// @brief 				Sets the terminal settings. Main use is to FLUSH or
/// 					DRAIN any data remaining after missexecuting
/// @param termios_p	Pointer to the termios settings structure
void	termios_setter(struct termios *termios_p);

/// @brief 				Initializes the shell and keeps looping until exit
/// @param script		Script structure (see minishell struct)
/// @param line_buffer	Line buffer
/// @return				void
/// static int	ms_loop(t_script *script);

/* ************************************************************************** */
///	signal.c
/* ************************************************************************** */

/// @brief 		Signal processing functions setter
/// @param  	No parameter required
void	signal_setter(void);

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler(int signum);

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler_fork(int signum);

/// @brief 			Handles the signal SIGINT when in heredoc
///					Exits with status 130 Command terminated by user
/// @param signum	The signal number
/// @return			void
void	sig_handler_heredoc(int signum);

/* ************************************************************************** */
///	parser.c
/* ************************************************************************** */

/// @brief		This function checks whether the given linked list, of tokens,
///				is a valid command syntaxically.
/// @param head	Head of the token list
/// @return		0 if success, 1 if failure
int		check_syntax(t_token *head);

/// @brief			This function simply counts the number of pipes in our
///					linked list of tokens to determine the number of chained
///					commands are in the line buffer.
/// @param head		Head of the token list
/// @return			Number of commands
int		get_cmd_count(t_token *head);

/// @brief		This function simply trims the leading and trailing whitespace
///				that can be found when replacing an environment variable.
/// @param head	Head of the token list
/// @return		Trimmed content
void	trim_spaces(t_token *head);

/// @brief			Determines the amount of arguments each command
///					has so the argv can be malloced to the right size in the
///					following steps.
/// @param head		Head of the token list
/// @param script	Script pointer
/// @return			Trimmed content
void	get_num_args(t_token *head, t_script *script);

/// @brief 			Iniatilzes file names direction and remove quotes from names
/// @param commands Struct witj info about files
/// @param max 		max number of files
/// @param head 	pointert o command struct hed
void	set_filenames_null(t_command *commands, int max, t_token *head);

/// @brief 		This function iterates through a linked list of tokens and
///				fills the command structure based on the type of token it
///				encounters.
/// @param head	Head of the token list
/// @param cmd	Command structure
/// @param i	Index
/// @param j	Index
/// @return		0 if success, 1 if failure
int		parse_commands(t_token *head, t_command *cmd, int i, int j);

/// @brief 			This function sets the open flags and opens the files
///					based on the type of redirection token it encounters
///					('<', '<<', '>', '>>').
/// @param head		Head of the token list
/// @param file		Redirection file structure
/// @return			0 if success, 1 if failure
int		redir(t_token *head, t_redirection *file);

/// @brief 		Creates a node in the file linked list withe file name
///				and adds it to the back of list
/// @param file	Struct linked list node
void	fill_heredoc(t_redirection *file);

/// @brief 				The script parser main function. All parsing starts here
/// @param script		The script pointer
/// @param line_buffer	The line buffer to parse
/// @return
int		parser(t_script *script, char **line_buffer);

/* ************************************************************************** */
///	quotes.c
/* ************************************************************************** */

/// @brief 		check if estring enclosing quotes are single or double
/// @param str	string to check
/// @return		1 if single quotes (' '), 0 if double quotes (" ")
///				MISLEADING CHANGE STATUS
int		first_quote(char *str);

/// @brief 		Check if the #quotation marks before index is odd or even.
/// @param str	string to check
/// @param i	termination index
/// @param c	quotation mark to check
/// @return		1 if #quotation before index i is odd, 0 if even
///				MISLEADING CHANGE STATUS
int		odd_before(char **str, int i, char c);

/// @brief 		Check if the #quotation marks after index is odd or even.
/// @param str	string to check
/// @param i	termination index
/// @param c	quotation mark to check
/// @return		1 if is odd, 0 if even
///				MISLEADING CHANGE STATUS
int		odd_after(char **str, int i, char c);

/// @brief 			Copies string contents between quotes
/// @param start 	Pointer at start quote
/// @param end 		pointer at end quote
/// @param str 		destination string
/// @param i 		destination index ??
///					NEEDS REFACTOR with LIBFT
void	copy_in_quotes(char *start, char *end, char **str, int *i);

/// @brief 		advances the given pointer to the next character that it is on
///				For example, if the function is called with the pointer pointing
///				at a quotation mark, it will advance the pointer in the string
///				to the next occurence of that same quotation mark. The function
///				returns 0 if this character is never met, which would signify
///				an unclosed quotation mark.
/// @param str	string to advance
/// @return		0 if unclosed quotation mark (error), 1 otherwise (success)
///				MISLEADING CHANGE STATUS
int		closed_quotes_check(char **str);

/// @brief 		cleanup after removing redundant quotes and frees up alloc
/// @param tmp	string to clean up
/// @param copy	string to clean up
/// @param i	termination index
/// @return		resulting cleanded string
char	*end_remove_quotes(char *tmp, char *copy, int i);

/// @brief 		removes redundant quotes
/// @param str	string to remove quotes
/// @return		string clean of quotes
char	*remove_quotes(char *str);

/* ************************************************************************** */
///	ms_tokens.c
/* ************************************************************************** */

/// @brief 		This function is here to treat off cases where a $ expansion
///				would lead to empty name tokens with the exception for an empty
///				token after a pipe.
/// @param head Head of the token list
/// @return		clean content
void	remove_blank_tokens(t_token *head);

/// @brief 				Creates a new token
/// @param string		String to be tokenized
/// @param size			Token size
/// @param type			Token type (as per enum t_token_type)
/// @return				New token
t_token	*tk_addnew(const char *string, int size, t_token_type type);

/// @brief 					get a pointer to last token in token list
/// @param token_pointer	pointer to token list
/// @return					pointer to last token
t_token	*tk_lst_last_getter(t_token *token_pointer);

/// @brief 			Adds new token to token list end
/// @param head		Head of the token list
/// @param new		New token to be added
void	tk_lst_addback(t_token **head, t_token *new);

/// @brief 			Searches for a token type by token char set
/// @param s		String to be searched for token char set
/// @return			Struct with token type information: token char set, size
///					and token type
t_ops	tk_type_getter(const char *s);

/// @brief 				Initializes the tk_getter
/// @param str			String to be tokenized
/// @param head			Head of the token list
/// @return				1 if success, 0 if error
int		tk_getter(char *str, t_token **head);

/// @brief 				Trims the token command from whitespaces
/// @param line_buffer	string input with script
/// @param head			pointer to the head of the token list
/// @param script		script structure
/// @return				SUCCESS if valid, ERROR if invalid
int		tk_builder(char **line, t_token **head, t_script *script);

/* ************************************************************************** */
///	ms_envp.c
/* ************************************************************************** */

/// @brief 		This function gets the environment variable name after a $ and
///				returns its corresponding value in the environment.
/// @param str	String to be parsed
/// @param envp	Environment variables
/// @param i	Index start
/// @return		replace variable
char	*replace_loop(char *str, char **envp, int *i);

/// @brief 			Splits the string on '$' and accounts for the possibility
///					that the string may begin with a '$'
/// @param line_buf	String to be split
/// @param before	Pointer to the string before the first '$'
/// @param i		Index start
/// @return			Split string
char	**init_split_before(char *line_buf, char **before, int *i);

/// @brief 				Replaces ARGS in a given string by the environment vars
///						by iterating through the string and replacing each
///						environment variable with its value.
/// @param line_buf		String to be parsed
/// @param envp			Environment variables
/// @param i			Index start
/// @param j			Index end
/// @return				String with ARGS replaced by envp vars
char	*replace_env_var(char *line_buf, char **envp, int i, int j);

/// @brief		This function replaces multiple spaces with a single space
/// @param str	String to be parsed
/// @return		String with multiple spaces replaced by a single space
char	*replace_multiple_space(char *str);

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param str	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*env_var_getter(char *str, char **envp);

/// @brief 				This function prints the environment variables
/// @param envp			Environment variables
/// @return				void
void	show_envp(char **envp);

/// @brief 			This function gets the environment variable index
/// @param var 		variable to be found
/// @param envp 	Environment variables
/// @return			Index of the variable
int		env_var_index_getter(char *var, char **envp);

/// @brief 				This function sets the environment variable
/// @param val 			Value to be set
/// @param var 			Variable to be set
/// @param envp 		Environment variables
/// @return 			0 if success, -1 if error
int		env_var_setter(char *val, char *var, char ***envp);

/* ************************************************************************** */
///	ms_exec.c
/* ************************************************************************** */

// int main(int ac, char **av, char **envp)
int		exec_one(t_script *s);

/// @brief 			Script exec function
/// @param script 	Script contents
int		execute(t_script *script);

/* ************************************************************************** */
///	ms_exec_utils.c
/* ************************************************************************** */

/// @brief		Test validity of shell variables
/// @param var	Variable name to be tested
/// @return		SUCCESS or ERROR
int	var_name_check(char *var);


/// @brief 				Executa um comando em um processo filho.
/// @param argv			Array de strings contendo os argumentos do comando
///             		com o nome do comando na primeira posição.
/// @param envp			Array de strings representando variáveis de ambiente.
/// @param input_fd		O descritor de arquivo para a entrada padrão (stdin)
///do processo filho. Pode ser STDIN_FILENO
///ou um descritor de arquivo de um pipe.
/// @param ouput_fd		O descritor de arquivo para a saída padrão (stdout)
/// do processo filho. Pode ser STDOUT_FILENO
///ou um descritor de arquivo de um pipe.
void	execute_do_cmd(char **argv, char **envp, int input_fd, int output_fd);

/// @brief 			Executa dois comandos em sequência com um pipe entre eles.
/// @param s		Estrutura contendo informações cmd a serem executados.
/// @param path_env		Array de strings representando o caminho do ambiente.
/// @return			0 em caso de sucesso, encerra o programa em caso de falha.
int		pipex(t_script *s, char **path_env);

/// @brief 			Splits a string into an array of strings using delimiter.
/// @param path 		String to be splited
/// @param delimiter 	character used as delimiter
/// @return 			String array containing splited string
//char	**split_path(char **path, char delimiter);
char	**split_path(char **path);

/* ************************************************************************** */
///	ms_error.c
/* ************************************************************************** */

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int		return_error(const char *msg, int system);

/* ************************************************************************** */
///	ms_bi_***.c
/* ************************************************************************** */

/// @brief Remove a variable from the environment
/// @param arg Arguments passed to unset command
/// @param envp Current environment variables
/// @return Updated environment variables
//char **bi_unset(char **arg, char **envp);
//char	**bi_unset(t_script *s);

/// @brief              count the number or env variables
/// @param envp         current environment variables
/// @return             number or varibles
int		env_count(char **envp);

/// @brief          add new environment variable to env

/// @brief 			Export PERMANENT environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int		bi_export(t_script *s, int n);

/// @brief 			Export TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int		bi_equal(t_script *s, int n);


/// @brief 			Builtin cd command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
//int		bi_cd(char **args);
//int		bi_cd(t_command commands, char **envp);
int		bi_cd(t_script *s, int n);

/// @brief 			Builtin echo command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
//int		bi_echo(char **args);
//int		bi_echo(t_command command);
int		bi_echo(t_script *s, int n);
/// ******** int		bi_echo(t_script *s);

/// @brief 			Builtin env command
/// @param args		Builtin command arguments
/// @param envp		Environment variables
/// @return			SUCCESS or ERROR
//int		bi_env(char **args, char **envp);
int		bi_env(t_script *s);

/// @brief 			Builtin exit command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
//int		bi_exit(char **args);
int		bi_exit(t_script *s, int n);

/// @brief 			Builtin pwd command
/// @param void		Builtin command arguments not required
/// @return			SUCCESS or ERROR
int		bi_pwd(t_script *s, int n);
//int		bi_pwd(void);

/// @brief 			Builtin unset command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
int		bi_unset(t_script *s, int n);
//int		unset(char *args[]);

/// @brief
/// @param cmd
/// @return
int		arg_count(char **cmd);

/// @brief			Checks if the given string is a valid number
/// @param str		String to be checked
/// @return			TRUE if valid, FALSE if invalid
int		ft_is_str_digit(char *str);

/// @brief 			Checks if the given string is a valid number
/// @param command	Command to be checked
/// @return
char	*get_location(char *command);

/* ************************************************************************** */
///	ms_free.c
/* ************************************************************************** */

/// @brief 			Frees the environment variables
/// @param my_envp	Environment variables
void	free_envp(char **my_envp);

/// @brief 			Frees the content of a split string
/// @param split	Split string to be freed
void	free_split(char **split);

/// @brief 		Frees the token list
/// @param head	Head of the token list
/// @return		1 if success, 0 if failure
int		free_tokens(t_token **head);

/// @brief 			Clears args on commands struct list and frees nodes
/// @param cmd 		list pointer
/// @param cmd_idx 	quantity of nodes to clear and free
/// @return 		SUCCESS or ERROR ?? needs coherence check
int		free_commands(t_command *cmd, int cmd_idx);

/* ************************************************************************** */
///	debug.c
/* ************************************************************************** */

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int		show_func(const char *func_name, int status, char *msg);

#endif
