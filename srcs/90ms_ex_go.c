/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   90ms_ex_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:03:30 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/31 16:38:46 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




int ex_child(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	char	** cmd_path;
	
	cmd_path = split_path(s->envp);
	free(s->envp);
	if (!cmd_path)
		return (return_error("Malloc", errno, 0));
	if (cdm_path != NULL)
	{
		
	}
	
	
}

int	ex_pipe(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int pid;
	
	if (pipe(s->fd) == -1)
		return (return_error("pipe", errno, 0));
	pid = fork();
	if (pid == -1)
		return (return_error("fork", errno, 0));
	if (pid == 0)
	{
		show_func(__func__, SHOW_MSG, "CHILD EX START");
		g_exit_status = ex_child(s, n);
		free_commands(s->cmds, s->cmd_count);
		free(s->envp);
		exit(g_exit_status);
	}
	else
	{
		waitpid(pid, &g_exit_status, NULL);
		show_func(__func__, SHOW_MSG, "CHILD EX END")
		if (WIFEXITED(&g_exit_status))
			g_exited_status = 128 + WTERMSIG(g_exit_status);
		bi_env_upd(s, n);
	}
	return (SUCCESS);
		
}

/// @brief 		Selects and Executes built in functions
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
static int	exec_go(t_script *s, int n)
{
	/// @brief 		Selects and Executes built in functions
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
static int	exec_go(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	return (ex_pipe(s, n));
}