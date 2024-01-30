/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   70ms_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:18:08 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/30 16:10:58 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	redir_out_truncate(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int	fd;

	fd = open(s->commands[n].out.name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("fd = %d\n", fd);
	if (fd == -1)
	{
		show_func(__func__, ERROR, "OPEN TRUNCATE mode");
		return (return_error(s->commands[n].out.name, errno, 0));
	}
	show_func(__func__, SHOW_MSG, "BEFORE DUP2");
	dup2(fd, STDOUT_FILENO);
	write(2, "after dup2\n", 11);
	show_func(__func__, SHOW_MSG, "AFTER  DUP2");
	close(fd);
	write(2, "after close\n", 12);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

static int	redir_out_append(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	//int	fd;

	s->fd[1] = open(s->commands[n].out.name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (s->fd[1] == -1)
	{
		show_func(__func__, ERROR, "OPEN APPEND mode");
		return (return_error(s->commands[n].out.name, errno, 0));
	}
	dup2(s->fd[1], STDOUT_FILENO);
	close(s->fd[1]);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

int	redir_out_go(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	if (s->commands[n].out.flag == 578)
	{
		show_func(__func__, SHOW_MSG, "GO Open TRUNCATE mode");
		return (redir_out_truncate(s, n));
	}
	else if (s->commands[n].out.flag == 1090)
	{
		show_func(__func__, SHOW_MSG, "GO Open APPEND  mode");
		return (redir_out_append(s, n));
	}
	show_func(__func__, SHOW_MSG, "Nothing done!\n");
	return (0);
}

int	redir_in_go(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	//int	fd;

	s->fd[0] = open(s->commands[n].in.name, O_RDONLY);
	if (s->fd[0] == -1)
	{
		show_func(__func__, SHOW_MSG, "ERROR OPEN file\n");
		return (return_error(s->commands[n].in.name, errno, 0));
	}
	dup2(s->fd[0], STDIN_FILENO);
	close(s->fd[0]);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
