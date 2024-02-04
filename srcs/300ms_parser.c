/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300ms_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/02 19:55:28 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 				Builds an error message string to be displayed
///						when a syntax error is encountered.
/// @malloc				New strings
/// @free				New strings
/// @param tk_content	String argument to include in the error message
/// @return				Error message string
int	syntax_error_msg(char *tk_content, int errms, int errsys)
{
	char	*msgr;
	char	*msgt;
	int		status;

	msgt = ft_strjoin("syntax error near unexpected token `", tk_content);
	msgr = ft_strjoin(msgt, "'");
	free(msgt);
	status = return_error(msgr, errms, errsys);
	free(msgr);
	return (status);
}


/// @brief		This function checks whether the given linked list, of tokens,
///				is a valid command syntaxically.
/// @param tk	Head of the token list
/// @return		0 if success, 1 if failure
int	check_syntax(t_token *tk)
{
	show_func(__func__, MY_START, NULL);
	if (tk && tk->type == TK_PIPE)
		return (syntax_error_msg(tk->content, 2, 0));
	while (tk)
	{
		if (!tk->next && (tk->type == TK_PIPE || tk->type == TK_R_IN
				|| tk->type == TK_R_OUT))
			return (syntax_error_msg(tk->content, 2, 0));
		if (tk->type == TK_PIPE && tk->next
			&& tk->next->type == TK_PIPE)
			return (syntax_error_msg(tk->next->content, 2, 0));
		if ((tk->type == TK_R_OUT || tk->type == TK_R_IN)
			&& (tk->next && tk->next->type != TK_NAME))
			return (syntax_error_msg(tk->next->content, 2, 0));
		tk = tk->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief			This function simply counts the number of pipes in our
///					linked list of tokens to determine the number of chained
///					cmds are in the line buffer.
/// @param tk		Head of the token list
/// @return			Number of cmds
int	get_cmd_count(t_token *tk)
{
	show_func(__func__, MY_START, NULL);
	int	count;

	count = 0;
	while (tk)
	{
		if (!count)
			count = 1;
		if (tk->type == TK_PIPE)
			count ++;
		tk = tk->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (count);
}

/// @brief			Replaces the token->content string with a new trimmed string
///					Trim removes leading and trailing white spaces
///	@malloc			TRIMMED string
///	@free			Pre TRIM string
/// @param tk	Head of the token list with token->content to be trimmed
/// @return			NOTHING
void	tk_trim_spaces(t_token *tk)
{
	char	*tmp;

	show_func(__func__, MY_START, NULL);
	while (tk)
	{
		tmp = tk->content;
		tk->content = ft_strtrim(tmp, " \t\v\r\n\f");
		free(tmp);
		tk = tk->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief			This function determines the amount of arguments each command
///					has so the argv can be malloced to the right size in the
///					following steps.
/// @param tk		Head of the token list
/// @param s	Script pointer
/// @return			Trimmed content
void	get_num_args(t_token *tk, t_script *s)
{
	t_token	*tmp;
	int		i;

	show_func(__func__, MY_START, NULL);
	i = 0;
	while (i < s->cmd_count)
	{
		s->cmds[i].argc = 0;
		tmp = tk;
		while (tk && tk->type != TK_PIPE)
		{
			if (tk->type == TK_NAME && (tmp->type != TK_R_IN
					&& tmp->type != TK_R_OUT))
				s->cmds[i].argc++;
			tmp = tk;
			tk = tk->next;
		}
		if (tk)
			tk = tk->next;
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief 			Iniatilzes file names direction and remove quotes from names
/// @param cmds Struct with info about files
/// @param max 		max number of files
/// @param tk 	pointert o command struct hed
void	set_filenames_null(t_command *cmds, int max, t_token *tk)
{
	int	i;

	show_func(__func__, MY_START, NULL);
	i = -1;
	while (++i < max)
	{
		cmds[i].in.name = NULL;
		cmds[i].out.name = NULL;
		cmds[i].in.heredoc = NULL;
	}
	while (tk)
	{
		show_func(__func__, SHOW_MSG, ft_strjoin("tk->content = ", tk->content));
		//tk->content = remove_quotes(tk->content);
		tk = tk->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief 		This function iterates through a linked list of tokens and
///				fills the command structure based on the type of token it
///				encounters.
/// @param tk	Head of the token list
/// @param cmd	Command structure
/// @param i	Index of the commands
/// @param j	Index of the arguments
/// @return		0 if success, 1 if failure
int	parse_commands(t_token *tk, t_command *cmd, int i, int j)
{
	show_func(__func__, MY_START, NULL);
	while (tk)
	{
		cmd[i].argv = malloc(sizeof(char *) * (cmd[i].argc + 1));
		if (!cmd[i].argv)
			return (1);
		j = 0;
		while (tk && tk->type != TK_PIPE)
		{
			if (tk->type == TK_NAME)
				cmd[i].argv[j++] = ft_strdup(tk->content);
			else if (tk->type == TK_R_IN && redir(tk, &cmd[i].in))
				return (free_commands(cmd, i + 1));
			else if (tk->type == TK_R_OUT && redir(tk, &cmd[i].out))
				return (free_commands(cmd, i + 1));
			if (tk->type == TK_R_IN || tk->type == TK_R_OUT)
				tk = tk->next;
			if (tk)
				tk = tk->next;
		}
		if (tk)
			tk = tk->next;
		cmd[i].argv[j] = NULL;
		i++;
	}
	show_func(__func__, SUCCESS, "03");
	return (0);
}

/// @brief 			This function sets the open flags and opens the files
///					based on the type of redirection token it encounters
///					('<', '<<', '>', '>>').
/// @param tk		Head of the token list
/// @param file		Redirection file structure
/// @return			0 if success, 1 if failure
int	redir(t_token *tk, t_redirection *file)
{
	int		ret;

	show_func(__func__, MY_START, NULL);
	if (file->name)
		free(file->name);
	if (!tk->next || tk->next->type != TK_NAME)
		return (0);
	file->name = ft_strdup(tk->next->content);
	if (!ft_strncmp(tk->content, ">>", 2))
		file->flag = (O_CREAT | O_APPEND | O_RDWR);
	else if (!ft_strncmp(tk->content, "<<", 2))
		fill_heredoc(file);
	else if (!ft_strncmp(tk->content, ">", 1))
		file->flag = (O_CREAT | O_TRUNC | O_RDWR);
	else if (!ft_strncmp(tk->content, "<", 1))
		file->flag = O_RDONLY;
	if (file->flag == -1)
		return (0);
	ret = open(file->name, file->flag, 0644);
	if (ret == -1)
		return (return_error(file->name, 0, 1));
	close(ret);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

/// @brief 		Creates a node in the file linked list withe file name
///				and adds it to the back of list
/// @param file	Struct linked list node
void	fill_heredoc(t_redirection *file)
{
	t_list	*tmp;

	show_func(__func__, MY_START, NULL);
	tmp = ft_lstnew(ft_strdup(file->name));
	if (file->heredoc == NULL)
		file->heredoc = tmp;
	else
		ft_lstadd_back(&file->heredoc, tmp);
	file->flag = -1;
	show_func(__func__, SUCCESS, NULL);
}

/// @brief 				The script parser main function. All parsing starts here
/// @param s			The script pointer
/// @param line_buffer	The line buffer to parse
/// @return
int	parser(t_script *s, char **line_buffer)
{
	t_token	*tk;

	show_func(__func__, MY_START, NULL);
	tk = NULL;
	*line_buffer = readline("\001\033[1;94m\002 Minishell > \001\033[0m\002");
	if (!*line_buffer)
	{
		show_func(__func__, MALLOC_ERROR, NULL);
		return (2);
	}
	add_history(*line_buffer);
	if (tk_builder(line_buffer, &tk, s))
		return (free_tokens(&tk));
	show_func(__func__, SHOW_MSG, "TOKEN LIST");
	show_token_list(tk);
	remove_blank_tokens(tk);
	if (check_syntax(tk))
		return (free_tokens(&tk));
	s->cmd_count = get_cmd_count(tk);
	s->cmds = malloc(sizeof(t_command) * s->cmd_count);
	if (!s->cmds || s->cmd_count <= 0)
		return (free_tokens(&tk));
	tk_trim_spaces(tk);
	get_num_args(tk, s);
	set_filenames_null(s->cmds, s->cmd_count, tk);

	if (parse_commands(tk, s->cmds, 0, 0))
	{
		show_func(__func__, SUCCESS, NULL);
		return (free_tokens(&tk));
	}
	free_tokens(&tk);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
