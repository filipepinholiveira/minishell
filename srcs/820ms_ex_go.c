/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   820ms_ex_go.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:03:30 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/01 12:48:27 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *path_finder(t_script *s, int n)
{
	char	*path_ex;
	char 	**path;
	int		i;
	
	path = split_path(s->envp);
	if (!path)
		return(NULL);
	i = -1;
	while(path[++i])
	{
		path_ex = ft_strjoin(path[i], s->cmds[n].argv[0]);
		if(!access(path_ex, F_OK))
			break;
		ft_free(path_ex);
	}
	ft_free_arr(path);
	if (path_ex)
		return (path_ex);
	return NULL;
}

char **cmd_copy(char **cmd_n, int argc)
{
	show_func(__func__, MY_START, NULL);
	char	**cmd_data;
	int		i;
		
	if (!cmd_n || !argc)
		return(NULL);
	cmd_data = (char **)malloc(sizeof(char *) * argc);
	if (!cmd_data)
		return (NULL);
	cmd_data[argc] = NULL;
	i = -1;
	while (++i < argc)
		cmd_data[i] = ft_strdup(cmd_n[i]);	
	return (cmd_data);
}

int ex_child(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	char	**cmd_vector;
	char	*path_ex;
		
	path_ex = path_finder(s, n);
	if (!path_ex)
		return(return_error("path not found", 2, 0));
	else
	{
		cmd_vector = cmd_copy(s->cmds[n].argv, s->cmds[n].argc);
		free_envp(s->envp);
		free_commands(s->cmds, s->cmd_count);
		if (execve(path_ex, cmd_vector, NULL) == -1)
		{
			return_error("command not found", 2, 1);
			exit(exit_status_getter(errno));
		}
	}
	return (ERROR);
}

int	ex_exec(t_script *s, int n)
{
	int status;

	if (redir_go(s, n))
		return (return_error("redir error", errno, 0));
	status = ex_child(s, n);
	return (status);
}

int	ex_pipe(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	pid_t pid;
	
	if (s->cmds[0].in.flag == -1)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, sig_handler_fork);
	signal(SIGINT, sig_handler_fork);
	if (pipe(s->fd) == -1)
		return (return_error("pipe", errno, 0));
	pid = fork();
	if (pid == -1)
		return (return_error("fork", errno, 0));
	if (pid == 0)
	{
		show_func(__func__, SHOW_MSG, "CHILD EX START");
		exit(ex_exec(s, n));
	}
	else
	{
		wait(&g_exit_status);
		show_func(__func__, SHOW_MSG, "CHILD EX END");
		if (WIFEXITED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
		bi_env_upd(s, n);
	}
	show_func(__func__, SUCCESS, "CHILD Builin executed");
	return (SUCCESS);
}

/// @brief 		Selects and Executes built in functions
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
int	exec_go(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	return (ex_pipe(s, n));
}