/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/29 13:41:37 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	execute_show(t_script *s)
{
	int	i = -1;
	int	j = -1;

	show_func(__func__, MY_START);
	printf("s->com_count: %i\n", s->cmd_count);
	while (++j < s->cmd_count)
	{
		printf("\n");
		while (++i < s->commands[j].argc)
		{
			printf("# s->commands[%i].argv[%i]: %s\n", 
				j, i, s->commands[j].argv[i]);
		}
		printf("  s->commands[%i].out.name: %s\n", j, s->commands[j].out.name);
		printf("  s->commands[%i].out.flag: %d\n", j, s->commands[j].out.flag);
		printf("  s->commands[%i].out->heredoc: %p\n", 
			j, s->commands[j].out.heredoc);
		printf("  s->commands[%i].in.name: %s\n", j, s->commands[j].in.name);
		printf("  s->commands[%i].in.flag: %d\n", j, s->commands[j].in.flag);
		printf("  s->commands[%i].in->heredoc: %p\n", 
			j, s->commands[j].in.heredoc);
		i = -1;
	}
	printf("\n");
	show_func(__func__, SUCCESS);
	return ;
}

int	execute_do(t_script *s)
{
	pid_t	child_pid;
	char	*cmd_path;

	show_func(__func__, MY_START);
	if (ft_strncmp(s->commands[0].argv[0], "echo", 5) == 0)
		//echo_print(s->commands[0].argv);
		echo_print(s);
	else if (ft_strncmp(s->commands[0].argv[0], "cd", 3) == 0)
		//cd_cmd(s->commands[0].argv);
		cd_cmd(s);
	else if (ft_strncmp(s->commands[0].argv[0], "pwd", 4) == 0)
		pwd_print();
	else if (ft_strncmp(s->commands[0].argv[0], "export", 7) == 0)
	{
		//s->envp = export_cmd(s->commands[0].argv, s->envp);
		s->envp = export_cmd(s);
	}
	else if (ft_strncmp(s->commands[0].argv[0], "unset", 6) == 0)
	{
		//s->envp = unset_cmd(s->commands[0].argv, s->envp);
		s->envp = unset_cmd(s);
	}
	else if (ft_strncmp(s->commands[0].argv[0], "env", 4) == 0)
		//env_print(s->commands[0].argv, s->envp);
		env_print(s);
	else if (ft_strncmp(s->commands[0].argv[0], "exit", 5) == 0)
		//exit_shell(s->commands[0].argv);
		exit_shell(s);
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			cmd_path = get_location(s->commands[0].argv[0]);
			if (cmd_path != NULL)
			{
				if (execve(cmd_path, s->commands[0].argv, NULL) == -1)
				{
					perror("Error");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				printf("%s: command not found\n", s->commands[0].argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(NULL);
	}
	show_func(__func__, SUCCESS);
	return (0);
}

/// @brief 		Script exec function
/// @param s 	Script contents
int	execute(t_script *s)
{
	show_func(__func__, MY_START);
	//char	**path_env;
	execute_show(s);
	//path_env = split_path(s->envp, ':');
	if (s->cmd_count == 1)
	{
		if (execute_do(s))
		{
			show_func(__func__, SUCCESS);
			return (1);
		}
	}
	else
		if (pipex(s, s->envp))
			return (1);
	//execute_do(s);
	//termios_setter(&s->termios_p);
	show_func(__func__, SUCCESS);
	return (SUCCESS);
}

/*

		if (strcmp(cmd[0], "echo") == 0)
			echo_print(cmd); // FEITO???
		else if (strcmp(cmd[0], "cd") == 0)
			cd_cmd(cmd); // FEITO
		else if (strcmp(cmd[0], "pwd") == 0)
		{
			pwd_print(); // FEITO???
		}
		else if (strcmp(cmd[0], "export") == 0)
			printf("Execute export with no options\n");
		else if (strcmp(cmd[0], "unset") == 0)
			printf("Execute unset with no options\n");
		else if (strcmp(cmd[0], "env") == 0)
		{
			env_print(cmd, envp); // FEITO
		}
		else if (strcmp(cmd[0], "exit") == 0)
		{
				exit_shell(cmd); // FEITO
		}
		else
			{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			// Processo filho
			char *command = get_location(cmd[0]);
			if (command != NULL) {
				if (execve(command, cmd, NULL) == -1) {
					perror("Error");
					exit(EXIT_FAILURE);
				}
			} else {
				// Tratar comandos que não existem no caminho especificado
				printf("%s: command not found\n", cmd[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			// Processo pai
			wait(NULL);
		}
	}
	}*/
