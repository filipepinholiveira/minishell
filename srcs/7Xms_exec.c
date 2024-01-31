/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7Xms_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/31 13:00:04 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_cmd_type(char *cmd)
{
	show_func(__func__, MY_START, NULL);
	if (ft_strncmp(cmd, "echo", 5) == SUCCESS)
		return (CMD_ECHO);
	else if (ft_strncmp(cmd, "cd", 3) == SUCCESS)
		return (CMD_CD);
	else if (ft_strncmp(cmd, "pwd", 4) == SUCCESS)
		return (CMD_PWD);
	else if (ft_strncmp(cmd, "export", 7) == SUCCESS)
		return (CMD_EXPORT);
	else if (ft_strncmp(cmd, "unset", 6) == SUCCESS)
		return (CMD_UNSET);
	else if (ft_strncmp(cmd, "env", 4) == SUCCESS)
		return (CMD_ENV);
	else if (ft_strncmp(cmd, "exit", 5) == SUCCESS)
		return (CMD_EXIT);
	else
		return (CMD_EXEC);
}

static int exit_status_getter(int status)
{
	show_func(__func__, MY_START, NULL);
	int i;
	const t_execve_error	ex_error[8] = {
		{EACCES, 126},
		{ENOMEM, 12},
		{E2BIG, 7},
		{EFAULT, 14},
		{EINVAL, 22},
		{EIO, 5},
		{0, 0}};

	i = -1;
	while (ex_error[++i].src_error)
		if (ex_error[i].src_error == status)
			return (ex_error[i].dest_error);
	return (SUCCESS);
}

/// @brief 		Selects and Executes built in functions
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
static int	exec_go(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_itoa(n));
	show_func(__func__, SUCCESS, NULL);
	pid_t	fork_pid;
	char	**cmd_path;
	char	*exec_path;
	int		i;
	int		status;

	i = -1;

	fork_pid = fork();
	signal(SIGINT, sig_handler_fork);
	if (fork_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (fork_pid == 0)
	{
		cmd_path = split_path(s->envp);
		if (cmd_path != NULL)
		{
			while (cmd_path[++i] != NULL)
			{
				exec_path = ft_strjoin(cmd_path[i], s->cmds[n].argv[0]);
				if (!access(exec_path, F_OK))
					break ;
			}
			if (cmd_path[i])
			{
				if (s->cmds[0].out.name)
				{
					printf("Reconhece p ficheiro de escrita e vai...  \n");
					if (s->cmds[0].out.flag == 578)
					{
						printf("abrir e truncar\n");
						int file = open(s->cmds[0].out.name, O_WRONLY | O_TRUNC);
						if (file == -1)
						{
							free(exec_path);
							return (ERROR);
						}
						dup2(file, STDOUT_FILENO);
						close (file);
					}
					if (s->cmds[0].out.flag == 1090)
					{
						printf("abrir e concatenar\n");
						int file = open(s->cmds[0].out.name, O_WRONLY | O_APPEND);
						if (file == -1)
						{
							free(exec_path);
							return (ERROR);
						}
						dup2(file, STDOUT_FILENO);
						close (file);
					}
					}
				if (s->cmds[0].in.name)
				{
					printf("Reconhece p ficheiro de leitura\n");
					int file = open(s->cmds[0].in.name, O_RDONLY);
					if (file == -1)
					{
						free(exec_path);
						return (ERROR);
					}
					dup2(file, STDIN_FILENO);
					close (file);
				}
				status = execve(exec_path, s->cmds[n].argv, NULL); // atençao que se entra no exec jao nao faz free!!! Filipe 17 jan
				if (status == -1)
				{
					perror("Error");
					exit(exit_status_getter(errno));
				}
				exit(SUCCESS);
			}
			free(exec_path);
			printf("%s: command not found\n", s->cmds[n].argv[0]);
			exit(COMMAND_NOT_FOUND);
		}
	}
	else
	{
		status = 500;
		waitpid(fork_pid, &g_exit_status, 0);
		printf("status = %d\n", status);
		if (WIFEXITED(g_exit_status))
		{
		    g_exit_status = WEXITSTATUS(g_exit_status);
			printf("Child process exited with status %d\n", g_exit_status);
		}
		printf("Saiu do child\n)");
	}
	return (g_exit_status);
}

/// @brief 		Executes a single command
/// @param s 	Parsed script with command(s) to Execute
/// @return		0 if success, 1 if failure,...
int	exec_one(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	if (ft_strchr(s->cmds[0].argv[0], '='))
	{
		show_func(__func__, SHOW_MSG, "Variable temp");
		g_exit_status = bi_equal(s, n);
	}
	else
	{
		if (s->cmds[0].argc && get_cmd_type(s->cmds[0].argv[0]) != CMD_EXEC)
			g_exit_status = bi_go(s, n);
		else
			g_exit_status = exec_go(s, n);
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

/// @brief 		Script exec function
/// @param s 	Script contents
int	execute(t_script *s)
{
	show_func(__func__, MY_START, NULL);
	char	**path_env;

	execute_show(s);
	path_env = split_path(s->envp);
	if (s->cmd_count == 1)
	{
		if (exec_one(s, 0))
		{
			show_func(__func__, SUCCESS, NULL);
			return (1);
		}
	}
	else
		if (exec_many(s, path_env))
			return (1);
	termios_setter(&s->termios_p);
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
