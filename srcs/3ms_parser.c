/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3ms_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/09 23:30:02 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief		This function checks whether the given linked list, of tokens,
///				is a valid command syntaxically.
/// @param head	Head of the token list
/// @return		0 if success, 1 if failure
int	check_syntax(t_token *head)
{
	// t_token	*tmp;

	// tmp = head;
	show_func(__func__, MY_START, NULL);
	if (head && head->type == TK_PIPE)
		return (return_error("Syntax error", 0));
	while (head)
	{
		if (!head->next && (head->type == TK_PIPE
				|| head->type == TK_R_IN
				|| head->type == TK_R_OUT))
			return (return_error("Syntax error", 0));
		if (head->type == TK_PIPE && head->next
			&& head->next->type == TK_PIPE)
			return (return_error("Syntax error", 0));
		if ((head->type == TK_R_OUT || head->type == TK_R_IN)
			&& (head->next && head->next->type != TK_NAME))
			return (return_error("Syntax error", 0));
		head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

/// @brief			This function simply counts the number of pipes in our
///					linked list of tokens to determine the number of chained
///					commands are in the line buffer.
/// @param head		Head of the token list
/// @return			Number of commands
int	get_cmd_count(t_token *head)
{
	show_func(__func__, MY_START, NULL);
	int	count;

	count = 0;
	while (head)
	{
		if (!count)
			count = 1;
		if (head->type == TK_PIPE)
			count ++;
		head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (count);
}

/// @brief		This function simply trims the leading and trailing whitespace
///				that can be found when replacing an environment variable.
/// @param head	Head of the token list
/// @return		Trimmed content
void	trim_spaces(t_token *head)
{
	char	*tmp;

	show_func(__func__, MY_START, NULL);
	while (head)
	{
	// if (s)
	// 	printf("s token = %s\n", s);
	// else
	// 	printf("s is empry\n");
		tmp = head->content;
		head->content = ft_strtrim(tmp, " \t\v\r\n\f");
		free(tmp);
		head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief			This function determines the amount of arguments each command
///					has so the argv can be malloced to the right size in the
///					following steps.
/// @param head		Head of the token list
/// @param script	Script pointer
/// @return			Trimmed content
void	get_num_args(t_token *head, t_script *script)
{
	t_token	*tmp;
	int		i;

	show_func(__func__, MY_START, NULL);
	i = 0;
	while (i < script->cmd_count)
	// if (s)
	// 	printf("s token = %s\n", s);
	// else
	// 	printf("s is empry\n");
	{
		script->commands[i].argc = 0;
		tmp = head;
		while (head && head->type != TK_PIPE)
		{
			if (head->type == TK_NAME && (tmp->type != TK_R_IN
					&& tmp->type != TK_R_OUT))
				script->commands[i].argc++;
			tmp = head;
			head = head->next;
		}
		if (head)
			head = head->next;
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief 			Iniatilzes file names direction and remove quotes from names
/// @param commands Struct witj info about files
/// @param max 		max number of files
/// @param head 	pointert o command struct hed
void	set_filenames_null(t_command *commands, int max, t_token *head)
{
	int	i;

	show_func(__func__, MY_START, NULL);
	i = -1;
	while (++i < max)
	{
		commands[i].in.name = NULL;
		commands[i].out.name = NULL;
		commands[i].in.heredoc = NULL;
	}
	while (head)
	{
		head->content = remove_quotes(head->content);
		head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief 		This function iterates through a linked list of tokens and
///				fills the command structure based on the type of token it
///				encounters.
/// @param head	Head of the token list
/// @param cmd	Command structure
/// @param i	Index
/// @param j	Index
/// @return		0 if success, 1 if failure
int	parse_commands(t_token *head, t_command *cmd, int i, int j)
{
	show_func(__func__, MY_START, NULL);
	while (head)
	{
		cmd[i].argv = malloc(sizeof(char *) * (cmd[i].argc + 1));
		if (!cmd[i].argv)
		{
			show_func(__func__, MALLOC_ERROR, "!cmd[i].argv");
			return (1);
		}
		j = 0;
		while (head && head->type != TK_PIPE)
		{
			if (head->type == TK_NAME)
				cmd[i].argv[j++] = ft_strdup(head->content);
			else if (head->type == TK_R_IN && redir(head, &cmd[i].in))
			{
				show_func(__func__, SUCCESS, "01");
				return (free_commands(cmd, i + 1));
			}
			else if (head->type == TK_R_OUT && redir(head, &cmd[i].out))
			{
				show_func(__func__, SUCCESS, "02");
				return (free_commands(cmd, i + 1));
			}
			if (head->type == TK_R_IN || head->type == TK_R_OUT)
				head = head->next;
			if (head)
				head = head->next;
		}
		if (head)
			head = head->next;
		cmd[i].argv[j] = NULL;
		i++;
	}
	show_func(__func__, SUCCESS, "03");
	return (0);
}

/// @brief 			This function sets the open flags and opens the files
///					based on the type of redirection token it encounters
///					('<', '<<', '>', '>>').
/// @param head		Head of the token list
/// @param file		Redirection file structure
/// @return			0 if success, 1 if failure
int	redir(t_token *head, t_redirection *file)
{
	int		ret;

	show_func(__func__, MY_START, NULL);
	if (file->name)
		free(file->name);
	if (!head->next || head->next->type != TK_NAME)
		return (0);
	file->name = ft_strdup(head->next->content);
	if (!ft_strncmp(head->content, ">>", 2))
		file->flag = (O_CREAT | O_APPEND | O_RDWR);
	else if (!ft_strncmp(head->content, "<<", 2))
		fill_heredoc(file);
	else if (!ft_strncmp(head->content, ">", 1))
		file->flag = (O_CREAT | O_TRUNC | O_RDWR);
	else if (!ft_strncmp(head->content, "<", 1))
		file->flag = O_RDONLY;
	if (file->flag == -1)
		return (0);
	ret = open(file->name, file->flag, 0644);
	if (ret == -1)
		return (return_error(file->name, 1));
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
/// @param script		The script pointer
/// @param line_buffer	The line buffer to parse
/// @return
int	parser(t_script *s, char **line_buffer)
{
	t_token	*token;

	show_func(__func__, MY_START, NULL);
	token = NULL;
	*line_buffer = readline("\001\033[1;94m\002 Minishell > \001\033[0m\002");
	if (!*line_buffer)
	{
		show_func(__func__, MALLOC_ERROR, NULL);
		return (2);
	}
	add_history(*line_buffer);
	if (tk_builder(line_buffer, &token, s))
		return (free_tokens(&token));
	remove_blank_tokens(token);
	if (check_syntax(token))
		return (free_tokens(&token));
	s->cmd_count = get_cmd_count(token);
	s->commands = malloc(sizeof(t_command) * s->cmd_count);
	if (!s->commands || s->cmd_count <= 0)
		return (free_tokens(&token));
	trim_spaces(token);
	get_num_args(token, s);
	set_filenames_null(s->commands, s->cmd_count, token);

	if (parse_commands(token, s->commands, 0, 0))
	{
		show_func(__func__, SUCCESS, NULL);
		return (free_tokens(&token));
	}
	free_tokens(&token);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
