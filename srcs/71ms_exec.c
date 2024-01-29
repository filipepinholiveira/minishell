/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/24 13:05:02 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	execute_show(t_script *s)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	show_func(__func__, MY_START, NULL);
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
	show_func(__func__, SUCCESS, NULL);
	return ;
}


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

//int	exec_bi(t_script *s, int bi_func, int i)

/// @brief 		Executes built in functions
/// @param f 	Builtin specific function to be called
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
int	exec_bi(int (*f)(t_script*, int), t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SUCCESS, NULL);
	return (f(s, n));
}

/// @brief 		Selects and Executes built in functions
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
static int	bi_go(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	const t_bi_cmd	bi_cmd[9] = {
	{"echo", bi_echo, s, n},
	{"cd", bi_cd, s, n},
	{"pwd", bi_pwd, s, n},
	{"export", bi_export, s, n},
	{"unset", bi_unset, s, n},
	{"env", bi_env, s, n},
	{"exit", bi_exit, s, n},
	{NULL, NULL, NULL, 0}};
	int				i;
	int				(*f)(t_script*, int);

	i = -1;

	while (bi_cmd[++i].bi_cmd)
	{

		signal(SIGINT, sig_handler_fork);
		if (!ft_strncmp(bi_cmd[i].bi_cmd, s->commands[n].argv[0],
				ft_strlen(bi_cmd[i].bi_cmd)))
		{
			if (s->commands[0].out.name)
				{
					printf("Reconhece p ficheiro de escrita e vai...  \n");
					if (s->commands[0].out.flag == 578)
					{
						printf("abrir e truncar\n");
						int file = open(s->commands[0].out.name, O_WRONLY | O_TRUNC);
						if (file == -1)
							return (ERROR);
						dup2(file, STDOUT_FILENO);
						close (file);
					}
					if (s->commands[0].out.flag == 1090)
					{
						printf("abrir e concatenar\n");
						int file = open(s->commands[0].out.name, O_WRONLY | O_APPEND);
						if (file == -1)
							return (ERROR);
						dup2(file, STDOUT_FILENO);
						close (file);
					}
				}
			if (s->commands[0].in.name)
				{
					printf("Reconhece p ficheiro de leitura\n");
					int file = open(s->commands[0].in.name, O_RDONLY);
					if (file == -1)
						return (ERROR);
					dup2(file, STDIN_FILENO);
					close (file);
				}
			f = bi_cmd[i].bi_func;
			return (f(bi_cmd[i].script, bi_cmd[i].n));
		}
	}
	show_func(__func__, ERROR, "Built in NOT found");
	return (-1);
}



static int exit_status_getter(int status)
{
	show_func(__func__, MY_START, NULL);
	int i;

	const t_execve_error ex_error[8] = {
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
				exec_path = ft_strjoin(cmd_path[i], s->commands[n].argv[0]);
				if (!access(exec_path, F_OK))
					break ;
			}
			if (cmd_path[i])
			{
				if (s->commands[0].out.name)
				{
					printf("Reconhece p ficheiro de escrita e vai...  \n");
					if (s->commands[0].out.flag == 578)
					{
						printf("abrir e truncar\n");
						int file = open(s->commands[0].out.name, O_WRONLY | O_TRUNC);
						if (file == -1)
						{
							free(exec_path);
							return (ERROR);
						}
						dup2(file, STDOUT_FILENO);
						close (file);
					}
					if (s->commands[0].out.flag == 1090)
					{
						printf("abrir e concatenar\n");
						int file = open(s->commands[0].out.name, O_WRONLY | O_APPEND);
						if (file == -1)
						{
							free(exec_path);
							return (ERROR);
						}
						dup2(file, STDOUT_FILENO);
						close (file);
					}
					}
				if (s->commands[0].in.name)
				{
					printf("Reconhece p ficheiro de leitura\n");
					int file = open(s->commands[0].in.name, O_RDONLY);
					if (file == -1)
					{
						free(exec_path);
						return (ERROR);
					}
					dup2(file, STDIN_FILENO);
					close (file);
				}
				status = execve(exec_path, s->commands[n].argv, NULL); // atençao que se entra no exec jao nao faz free!!! Filipe 17 jan
				if (status == -1)
				{
					perror("Error");
					exit(exit_status_getter(errno));
				}
				exit(SUCCESS);
			}
			free(exec_path);
			printf("%s: command not found\n", s->commands[n].argv[0]);
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


//useful info :::

					// printf("errno = %d \n", errno);
					// perror("Error");
					// free(exec_path);
					// 	/*errno possiveis:

					// EACCES (Permission denied):
					// Indica que não há permissão para executar o arquivo. valor costuma ser 13

					// ENOMEM (Out of memory):
					// Indica que não há memória disponível para executar o novo programa.
					// valor costuma ser 12

					// E2BIG (Argument list too long):
					// Indica que a soma do tamanho dos argumentos e do ambiente é maior 
					// do que o permitido.
					// valor costuma ser 7

					// EFAULT (Bad address):
					// Indica um problema com a estrutura de dados passada para a função execve. 
					// Por exemplo, um ponteiro nulo ou inválido.
					// valor costuma ser 14

					// EINVAL (Invalid argument):
					// Indica que um argumento passado para execve é inválido.
					// valor costuma ser 22

					// EIO    An I/O error occurred.
					// usado para indicar erros relacionados à entrada/saída. Ele indica um erro geral 
					// associado a operações de entrada/saída que não podem ser concluídas com sucesso.
					// valor costuma ser 5

					// */
					// if (errno == EACCES)
					// 	exit(PERMISSION_DENIED); // se colocarmos EACESS vai dar erro 13
					// else if (errno == ENOMEM)
					// 	exit(ENOMEM);
					// else if (errno == E2BIG)
					// 	exit(E2BIG);
					// else if(errno == EFAULT)
					// 	exit(EFAULT);
					// else if(errno == EINVAL)
					// 	exit(EINVAL);
					// else if(errno == EIO)
					// 	exit(EIO);
					// else
					// 	exit(ERROR);

// static int	exec_go(t_script *s, int n)
// {
// 	show_func(__func__, MY_START, NULL);
// 	show_func(__func__, SHOW_MSG, ft_itoa(n));
// 	show_func(__func__, SUCCESS, NULL);
// 	(void)s;
// 	(void)n;
// 	pid_t	child_pid;
// 	char	*cmd_path;

// 	child_pid = fork();
// 	if (child_pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (child_pid == 0)
// 	{
// 		cmd_path = get_location(s->commands[0].argv[0]); // nao vou usar get_location, tenho o split_path (ESTUDAR ACESS)
// 		//cmd_path = split_path(s->envp);
// 		if (cmd_path != NULL)
// 		{
// 			if (execve(cmd_path, s->commands[0].argv, NULL) == -1)
// 			{
// 				perror("Error");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		else
// 		{
// 			printf("%s: command not found\n", s->commands[0].argv[0]);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 		wait(NULL);
// 	return (0);
// }

int	exec_one(t_script *s)
{
	show_func(__func__, MY_START, NULL);
	if (ft_strchr(s->commands[0].argv[0], '='))
	{
		show_func(__func__, SHOW_MSG, "Variable temp");
		g_exit_status = bi_equal(s, s->cmd_count - 1);
	}
	else
	{
		if (get_cmd_type(s->commands[0].argv[0]) != CMD_EXEC)
			g_exit_status = bi_go(s, s->cmd_count - 1);
		else
			g_exit_status = exec_go(s, s->cmd_count - 1);
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
//if (!ft_strncmp(->commands->argv[1], "=", 1))
//criarna envt
	if (s->cmd_count == 1)
	{
		if (exec_one(s))
		{
			show_func(__func__, SUCCESS, NULL);
			return (1);
		}
	}
	else
		if (pipex(s, path_env))
			return (1);
	termios_setter(&s->termios_p);
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}