/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:28:06 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/31 13:00:04 by antoda-s         ###   ########.fr       */
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

/// @brief 				Struct to hold errors from execve
/// @param src_error	error from execve status
/// @param dest_error	error
typedef struct s_execve_error
{
	const int	src_error;
	const int	dest_error;
}				t_execve_error;

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
	void			*s;
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
/// @param cmds		Commands to be executed
/// @param cmd_count	Number of cmds
/// @param exit_status	Exit status
/// @param envp			Environment variables
/// @param termios_p	Terminal settings
typedef struct s_script
{
	t_command		*cmds;
	int				cmd_count;
	int				exit_status;
	char			**envp;
	char			**envt;
	struct termios	termios_p;
	int				fd[2];
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
///	10ms_main.c
/* ************************************************************************** */

/// @brief 		Creates array from system environment variables
/// @param envp system environment variables from main (... char **envp)
/// @return 	array copy of system environment variables
/// static char	**envp_getter(char **envp);

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
///	20ms_signal.c
/* ************************************************************************** */

/// @brief 		Signal processing functionsError encountered while testing setter
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
///	30ms_parser.c
/* ************************************************************************** */

/// @brief		This function checks whether the given linked list, of tokens,
///				is a valid command syntaxically.
/// @param head	Head of the token list
/// @return		0 if success, 1 if failure
int		check_syntax(t_token *head);

/// @brief			This function simply counts the number of pipes in our
///					linked list of tokens to determine the number of chained
///					cmds are in the line buffer.
/// @param head		Head of the token list
/// @return			Number of cmds
int		get_cmd_count(t_token *head);

/// @brief			Replaces the token->content string with a new trimmed string
///					Trim removes leading and trailing white spaces
///	@malloc			TRIMMED string
///	@free			Pre TRIM string
/// @param tk_head	Head of the token list with token->content to be trimmed
/// @return			NOTHING
void	tk_trim_spaces(t_token *tk_head);

/// @brief			Determines the amount of arguments each command
///					has so the argv can be malloced to the right size in the
///					following steps.
/// @param head		Head of the token list
/// @param script	Script pointer
/// @return			Trimmed content
void	get_num_args(t_token *head, t_script *script);

/// @brief 			Iniatilzes file names direction and remove quotes from names
/// @param cmds Struct witj info about files
/// @param max 		max number of files
/// @param head 	pointert o command struct hed
void	set_filenames_null(t_command *cmds, int max, t_token *head);

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
///4ms_quotes.c
/* ************************************************************************** */

/// @brief 		fetchs for closed / unclosed quotes type " or '
///				the function must be called with the arg str (string)
///				starting with at a quotation mark.
///				The function seeks for the next occurrence of that quation mark
///				and sets str pointer to that next occurrence if found
///				or sets str pointer to the end {\0}
///				@malloc	: NOTHING
///				@free	: NOTHING
/// @param str	address of string, 1st char must be a quotation mark
/// @return		ERROR (unclosed), SUCCES (closed)
int		tk_quotes_checker(char **str);

/// @brief 		Unquotes a string. Special rules applies
///				- removes ' from limits = 'string'
///				- removes " from limts = "string", "string, string"
///				- (')  and (") are never inspected inside string
///				@malloc	: NOTHING
///				@free	: NOTHING
/// @param str	String to be unquoted
/// @return		A new unquoted string
char	*tk_xpd_unquote(char *str);

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

int tk_var_xpd_splits(char *oToken);
int	var_name_checker(char c);
int	var_firstchar(char c);
char **tk_var_xpd(char *oToken);
char	*tk_xpd_filler(char ***new_tk, char **envp);


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
char	**env_var_detector(char *line_buf, char **before, int *i);

/// @brief 				Replaces ARGS in a given string by the environment vars
///						by iterating through the string and replacing each
///						environment variable with its value.
/// @param line_buf		String to be parsed
/// @param envp			Environment variables
/// @param i			Index start
/// @param j			Index end
/// @return				String with ARGS replaced by envp vars
char	*env_var_expander(char *oldToken, char **envp);
// char	*env_var_expander(char *line_buf, char **envp, int i, int j);

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

/// @brief 		Executes a command
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @return		SUCCESS or ERROR
int		exec_one(t_script *s, int n);

/// @brief 			Script exec function
/// @param s 		Script contents
int		execute(t_script *s);

/* *************************************************/

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
int		exec_many(t_script *s);

/// @brief 			Splits a string into an array of strings using delimiter.
/// @param path 		String to be splited
/// @param delimiter 	character used as delimiter
/// @return 			String array containing splited string
//char	**split_path(char **path, char delimiter);
char	**split_path(char **path);

/***************** redirs *******************/

int	redir_in_go(t_script *s, int n);
int	redir_out_go(t_script *s, int n);



/* ************************************************************************** */
///	ms_error.c
/* ************************************************************************** */

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	export_error(const char *msg, int system);

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int		return_error(const char *msg, int errms, int errbash);

/* ************************************************************************** */
///	ms_bi_***.c
/* ************************************************************************** */

/// @brief 		Selects and Executes built in functions
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
int		bi_go(t_script *s, int n);


/* ************************************************************************** */
///	82ms_bi_echo.c
/* ************************************************************************** */

/// @brief 			Builtin echo command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
//int		bi_echo(char **args);
//int		bi_echo(t_command command);
int		bi_echo(t_script *s, int n);

/// ******** int		bi_echo(t_script *s);
/// @brief 			Builtin echo command env var '_' update (last cmd)
/// @param s		Parsed script with command(s) to execute
/// @param n		Index of cmd to executes
/// @return			SUCCESS if success, ERROR if error
int		bi_env_upd(t_script *s, int n);

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
//int		bi_cd(t_command cmds, char **envp);
int		bi_cd(t_script *s, int n);


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

/// @brief 			Remove a variable from the PERRMANENT environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int		bi_unset(t_script *s, int n);
//int		unset(char *args[]);

/// @brief 			Remove a variable from the TEMPORARY environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int	bi_unset_envt(t_script *s, int n);

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

/// @brief 			Clears args on cmds struct list and frees nodes
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
void	execute_show(t_script *s);
void show_token_list(t_token *token);

#endif
