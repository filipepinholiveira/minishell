/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 20:11:48 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// show_func(__func__, MY_START, NULL);
	int errors;

	errors = 0;
	while (tk)
	{
		// cmd[i].argv = malloc(sizeof(char *) * (cmd[i].argc + 1));
		cmd[i].argv = ft_calloc((cmd[i].argc + 1), sizeof(char *));
		if (!cmd[i].argv)
		{
			return_error("", errno, 1); // adicionada Filipe 19fev
			return (ERROR);
		}
		j = 0;
		while (tk && tk->type != TK_PIPE)
		{
			if (tk->type == TK_NAME)
				cmd[i].argv[j++] = ft_strdup(tk->content);
			else if (tk->type == TK_R_IN && redir(tk, &cmd[i].in))
				errors = 1;//return (free_commands(cmd, i + 1));
			else if (tk->type == TK_R_OUT && redir(tk, &cmd[i].out))
				errors = 1 ;//return (free_commands(cmd, i + 1));
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
	if (errors)
		return (free_commands(cmd, i));
	return (SUCCESS);
}

/// @brief 				The script parser main function. All parsing starts here
/// @param s			The script pointer
/// @param line_buffer	The line buffer to parse
/// @return
int	parser(t_script *s, char **line_buffer)
{
	// show_func(__func__, MY_START, NULL);
	t_token	*tk;

	tk = NULL;
	*line_buffer = readline("\001\033[1;94m\002Minishell > \001\033[0m\002");
	if (!*line_buffer)
		return (return_error("readline error\n", 2, 0));
	add_history(*line_buffer);
	if (tk_builder(line_buffer, &tk, s) == ERROR)
		return (free_tokens(&tk));
	//tk_rm_blank(tk);
	if (syntax_checker(tk))
		return (free_tokens(&tk));
	s->cmd_count = cmds_counter(tk);
	s->cmds = ft_calloc(s->cmd_count, sizeof(t_command));
	// s->cmds = malloc(sizeof(t_command) * s->cmd_count);
	show_pointer(__func__, D_MALLOC, "s->cmds", s->cmds);
	if (!s->cmds || s->cmd_count <= 0)
	{
		return_error("", errno, 1);
		return (free_tokens(&tk));
	}
	//tk_trim_spaces(tk);

	// show_token_list(tk);

	args_counter(tk, s);
	fnames_clear(s->cmds, s->cmd_count, tk);
	if (parse_commands(tk, s->cmds, 0, 0))
		return (free_tokens(&tk));
	free_tokens(&tk);
	return (SUCCESS);
}
