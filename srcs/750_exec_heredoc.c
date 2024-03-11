/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   750_exec_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:48:24 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/10 23:45:32 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			This function notifies heredoc error message
/// @param msg 		Content to be printed
void	error_message_heredoc(char *msg)
{
	show_func(__func__, MY_START, NULL);
	ft_putstr_fd("Minishell: warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted '", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("\')", 2);
}

/// @brief		This function reads the user's input until it finds the
/// 			delimiters set in heredoc linked list. It stores the input only
/// 			for the last delimiter and places it in the pipe for later use
/// 			as the input redirection.
/// @param h 	Pointer to the heredoc linked list
/// @param pipe Pointer to the pipe to output result
void	loop_heredoc(t_list *h, int pipe)
{
	show_func(__func__, MY_START, NULL);
	char	*tmp;
	char	*bis;

	bis = ft_strdup("");
	while (h)
	{
		tmp = readline("> ");
		if (!tmp || !ft_strncmp(tmp, h->content, ft_strlen(h->content) + 1))
		{
			if (!tmp)
				error_message_heredoc(h->content);
			h = h->next;
			free(tmp);
			continue ;
		}
		if (!h->next)
		{
			tmp = ft_strjoin_free(tmp, ft_strdup("\n"));
			bis = ft_strjoin_free(bis, tmp);
		}
		else
			free(tmp);
	}
	write(pipe, bis, ft_strlen(bis));
	free(bis);
}

/// @brief		This function first initializes a pipe in which we can write
/// 			the content that we'll read from the user.
/// @param s 	Script contents and parameters including redirect info
/// @param i 	Index of the command to be executed
/// @param path Commands execution path
void	heredoc(t_script *s, int i, char **path)
{
	show_func(__func__, MY_START, NULL);
	int		pipe_tmp[2];

	if (pipe(pipe_tmp) == -1)
	{
		free_cmds_path(s, path);
		exit((return_error("", errno, 1)));
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_heredoc);
	loop_heredoc(s->cmds[i].in.heredoc, pipe_tmp[1]);
	if (pipe_tmp[0] != STDIN_FILENO)
	{
		if (dup2(pipe_tmp[0], STDIN_FILENO) == -1)
		{
			write(2, "Error: dup2 failed\n", 19);
			pipe_closer(pipe_tmp, NULL);
			free_cmds_path(s, path);
			exit(ERROR);
		}
	}
	close(pipe_tmp[0]);
	close(pipe_tmp[1]);
}
