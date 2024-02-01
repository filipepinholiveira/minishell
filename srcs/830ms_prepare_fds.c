/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   830ms_prepare_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:24:33 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/01 16:31:56 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	prepare_fds(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	
	if (n == 0)
	{
		close (s->fd[0]);
		dup2(s->fd[1], STDOUT_FILENO);
		close (s->fd[1]);
	}
	else if (n == s->cmd_count)
	{
		close (s->fd[1]);
		dup2(s->fd[0], STDOUT_FILENO);
		close (s->fd[0]);
	}
	else
	{
		dup2(STDIN_FILENO, s->fd[0]);
		dup2(s->fd[1], STDOUT_FILENO);
		close(s->fd[0]);
		close(s->fd[1]);
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
