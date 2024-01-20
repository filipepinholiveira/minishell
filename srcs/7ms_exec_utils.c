/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:00:28 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/15 11:23:48 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief		Test validity of shell variables
/// @param var	Variable name to be tested
/// @return		SUCCESS or ERROR
int	var_name_check(char *var)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	i = 0;
	show_func(__func__, SHOW_MSG, var);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			show_func(__func__, ERROR, NULL);
			return (ERROR);
		}
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

// static void	execute_do_cmd_1(char **argv, char **envp, int in_fd)
// {
// 	show_func(__func__, MY_START, argv[0]);
// 	printf("input fd: %d\n", in_fd);
// 	printf("envp: %s\n", envp[0]);
// 	show_func(__func__, SUCCESS, NULL);
// 	return ;
// }

static void	execute_do_cmd_1(t_script *s, int index, int pipe_in)
{
	show_func(__func__, MY_START, s->commands->argv[index]);
	printf("out fd: %d\n", pipe_in);
	printf("envp: %s\n", s->envp[0]);

	pid_t	fork_pid;
	char	**cmd_path;
	char	*exec_path;
	int i;

	i = -1;

	signal(SIGINT, sig_handler_fork);
	fork_pid = fork();
	if (fork_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (fork_pid == 0)
	{
		printf("Entra no child criado pelo 1º cmd no Pipex\n");
		cmd_path = split_path(s->envp);
		if (cmd_path != NULL)
		{
			while (cmd_path[++i] != NULL)
			{
				exec_path = ft_strjoin(cmd_path[i], s->commands[index].argv[0]);
				if (!access(exec_path, F_OK))
					break ;
			}
		if (cmd_path[i])
		{
			dup2(1, pipe_in);
			printf("EXCVE no CMD_1 vai ser executado\n");
			int status = execve(exec_path, s->commands[0].argv, NULL); // atençao que se entra no exec jao nao faz free!!! Filipe 17 jan
			if (status)
			{
				perror("Error");
				//exit(exit_status_getter(errno));
			}
		}
		free(exec_path);
		printf("%s: command not found\n", s->commands[index].argv[0]);
		exit(COMMAND_NOT_FOUND);
		}
	}

	waitpid(fork_pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
	{
		g_exit_status = WEXITSTATUS(g_exit_status);
		printf("Child process exited with status %d\n", g_exit_status);
	}
	printf("Saiu do child criado 1º cmd no Pipex\n)");

	show_func(__func__, SUCCESS, NULL);
	return ;
}

//static void	execute_do_cmd_n(char **argv, char **envp, int in_fd, int out_fd)
static void	execute_do_cmd_n(t_script *s, int index, int in_fd, int out_fd)
{
	show_func(__func__, MY_START, s->commands[index].argv[0]);
	printf("input fd: %d\n", in_fd);
	printf("output fd: %d\n", out_fd);
	printf("envp: %s\n", s->envp[0]);

	pid_t	fork_pid;
	char	**cmd_path;
	char	*exec_path;
	int i;

	i = -1;

	signal(SIGINT, sig_handler_fork);
	fork_pid = fork();
	if (fork_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (fork_pid == 0)
	{
		printf("Entra no child criado pelo ultimo cmd no Pipex\n");
		cmd_path = split_path(s->envp);
		if (cmd_path != NULL)
		{
			while (cmd_path[++i] != NULL)
			{
				exec_path = ft_strjoin(cmd_path[i], s->commands[0].argv[index]);
				if (!access(exec_path, F_OK))
					break ;
			}
		if (cmd_path[i])
		{

			dup2(in_fd, STDIN_FILENO);
			dup2(out_fd, STDOUT_FILENO);
			printf("EXCVE no CMD_LAST vai ser executado com o com\n");
			int status = execve(exec_path, s->commands[0].argv, NULL); // atençao que se entra no exec jao nao faz free!!! Filipe 17 jan
			
			if (status)
			{
				perror("Error");
				//exit(exit_status_getter(errno));
			}
		}
		free(exec_path);
		printf("%s: command not found\n", s->commands[0].argv[index]);
		exit(COMMAND_NOT_FOUND);
		}
	}

	waitpid(fork_pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
	{
		g_exit_status = WEXITSTATUS(g_exit_status);
		printf("Child process exited with status %d\n", g_exit_status);
	}
	printf("Saiu do child criado ULTIMO cmd no Pipex\n)");

	show_func(__func__, SUCCESS, NULL);
	return ;


	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief 				Executa um comando em um processo filho.
/// 					Esta função cria um processo filho para executar o
///                     comando representado
/// 					pelos argumentos `argv` usando a chamada de sistema
///                     execve. O processo pai
/// 					espera pela conclusão do processo filho e,
///                      opcionalmente, verifica o status
/// 					de saída.
/// @param argv			Array de strings contendo os argumentos do comando,
///                     com o nome do comando na primeira posição.
/// @param envp			Array de strings representando variáveis de ambiente.
/// @param in_fd		O descritor de arquivo para a entrada padrão
///                     (stdin) do processo filho. Pode ser STDIN_FILENO
///                     ou um descritor de arquivo de um pipe.
/// @param out_fd		O descritor de arquivo para a saída padrão (stdout)
///                     do processo filho. Pode ser STDOUT_FILENO
///                     ou um descritor de arquivo de um pipe.









void	execute_do_cmd_i(char **argv, char **envp, int in_fd, int out_fd)
{
	show_func(__func__, MY_START, argv[0]);
	pid_t	child_pid;
	int		status;
	char	*cmd_path;
		// verificar o status se necessário
		// if (WIFEXITED(status)) {
		//     printf("Child process exited with status %d\n",
		// 			WEXITSTATUS(status));
		// }
	child_pid = fork();
	if (MY_DEBUG)
		return ;
	printf("entrou no fork\n");
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		printf("child_pid = 0 no execute_do_cmd\n");
		// Processo filho
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		printf("ARGV 0: %s\n", argv[0]);
		cmd_path = get_location(argv[0]);
		printf("CMD_PATH: %s\n", cmd_path);
		if (cmd_path != NULL)
		{
			printf("EXECVE entrada");
			if (execve(cmd_path, argv, envp) == 1)
			{
			// Se o execve falhar
			perror("execve");
			//Com essa informação, você poderá identificar se há
			/// algum problema com o caminho do executável
			/// ou se o arquivo executável está ausente.
			exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		// Processo pai
		waitpid (child_pid, &status, 0);
		// verificar o status se necessário
		// if (WIFEXITED(status)) {
		//     printf("Child process exited with status %d\n",
		//		WEXITSTATUS(status));
		// }
	}
	show_func(__func__, SUCCESS, NULL);
}

// /// @brief 		Executa dois comandos em sequência com um pipe entre eles.
// /// @param s	Estrutura contendo informações sobre cmds a serem executados.
// /// @param path_env		Array de strings representando o caminho do ambiente.
// /// @return			0 em caso de sucesso, encerra o programa em caso de falha.
// int	pipex(t_script *s, char **path_env)
// {
// 	show_func(__func__, MY_START, NULL);
// 	int		p[2];
// 	pid_t	child_pid;
// 	int 	i;

// 	signal(SIGINT, sig_handler_fork);
// 	i = 1;
// 	if (pipe(p) == -1)
// 	{
// 		perror("pipe");
// 		show_func(__func__, EXIT_FAILURE, NULL);
// 		exit(EXIT_FAILURE);
// 	}
// 	child_pid = fork();
// 	if (child_pid == -1)
// 	{
// 		perror("fork");
// 		show_func(__func__, ERROR, NULL);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (child_pid == 0)
// 	{
// 		// Processo filho
// 		printf("Executa o primeiro comando child\n");
// 		//close(pipe_fd[0]); // Fecha a extremidade de leitura do pipe
// 		// Redireciona stdout para a extremidade de escrita do pipe
// 		//dup2(pipe_fd[1], STDOUT_FILENO);
// 		//printf("Executa o primeiro comando child 2\n");

// 		while(i <= s->cmd_count)
// 		{
// //			int j = 0;
// 			if (i == 1)
// 			{
// 				//first command
// 				close(p[0]);
// 				execute_do_cmd_1(s->commands[i-1].argv, path_env, p[1]);
// 			}
// 			else if (i == s->cmd_count)
// 			{
// 				//last command
// 				close(p[1]);
// 				execute_do_cmd_n(s->commands[i-1].argv, path_env, p[0], STDOUT_FILENO);
// 				close(p[0]);
// 			}
// 			else
// 			{
// 				dup2(p[0], STDIN_FILENO);
// 				dup2(p[1], STDOUT_FILENO);
// 				execute_do_cmd_i(s->commands[i-1].argv, path_env, STDIN_FILENO, p[1]);
// 				// inbetween commands
// 			}
// 			// while (s->commands[i].argv[j])
// 			// {
// 			// 	execute_do_cmd(s->commands[i-1].argv, path_env, STDIN_FILENO, p[1]);
// 			// 	i++;
// 			// }
// 			i++;
// 		}
// 		// execute_do_cmd(s->commands[i].argv, path_env,
// 		// 	STDIN_FILENO, pipe_fd[1]);
// 		close(p[1]); // Fecha a extremidade de escrita do pipe
// 		show_func(__func__, CHILD_EXIT, "pipex simulator exit");
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		// Processo pai
// 		// close(pipe_fd[1]); // Fecha a extremidade de escrita do pipe
// 		// // Redireciona stdin para a extremidade de leitura do pipe
// 		// dup2(pipe_fd[0], STDIN_FILENO);
// 		// // Executa o segundo comando
// 		// execute_do_cmd(s->commands[1].argv, path_env, pipe_fd[0],
// 		// close(pipe_fd[0]); // Fecha a extremidade de leitura do pipe
// 		// 	STDOUT_FILENO);
// 		// // Aguarda o processo filho terminar
// 		wait(NULL);
// 	}
// 	show_func(__func__, SUCCESS, NULL);
// 	return (0);
// }




/// @brief 		Executa dois comandos em sequência com um pipe entre eles.
/// @param s	Estrutura contendo informações sobre cmds a serem executados.
/// @param path_env		Array de strings representando o caminho do ambiente.
/// @return			0 em caso de sucesso, encerra o programa em caso de falha.
int	pipex(t_script *s, char **path_env)
{
	show_func(__func__, MY_START, NULL);
	int cmd_num = s-> cmd_count;
	int		pipes[cmd_num + 1][2];
	pid_t	child_pids[cmd_num];
	int 	i;

	signal(SIGINT, sig_handler_fork);  // tratsignal(SIGINT, sig_handler_fork);amento de sinais
	
	i = -1;
	while (++i < cmd_num -1) // criaçao dos pipes 
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			show_func(__func__, EXIT_FAILURE, NULL);
			exit(EXIT_FAILURE);
		}
	}
	i = -1;
	while(++i < cmd_num) // criaçao dos processos nos childs
	{
		child_pids[i] = fork();
		if (child_pids[i] == -1)
		{
			perror("fork");
			show_func(__func__, ERROR, NULL);
			exit(EXIT_FAILURE);
		}
		if (child_pids[i] == 0) 
		{
			// entra no processo child
			int j = -1;
			printf("i no pipex: %d\n", i);
			printf("Cmd_num no pipex: %d\n", cmd_num);
			while(++j < cmd_num) // fechar pipes nao utilizados
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close (pipes[j][1]);
			}

			// executar commando
			if (i + 1 == 1)
			{
				//first command
				//close(p[0]);
				execute_do_cmd_1(s, i, pipes[i][1]);
			}
			else if (i + 1 == cmd_num)
			{
				//last command
				//close(p[1]);
				execute_do_cmd_n(s, i, pipes[i][0], pipes[i][1]);
				//close(p[0]);
			}
			else
			{
				dup2(pipes[j][0], STDIN_FILENO);
				dup2(pipes[j][1], STDOUT_FILENO);
				execute_do_cmd_i(s->commands[i].argv, path_env, STDIN_FILENO, pipes[i][1]);
				// inbetween commands
			}

		//close(pipes[i][0]);
		close (pipes[i][1]);
		show_func(__func__, CHILD_EXIT, "pipex simulator exit");
		exit(EXIT_SUCCESS);
		}
		// main process
		else
		{
		waitpid(child_pids[i], &g_exit_status, 0);
		}
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}




/// @brief 			Splits a string into an array of strings using a delimiter.
/// @param path 		String to be splited
/// @param delimiter 	character used as delimiter
/// @return 			String array containing splited string
// char	**split_path(char **path, char delimiter)
// {
// 	size_t	count;
// 	size_t	i;
// 	size_t	j;
// 	size_t	start;
// 	char	*current;
// 	char	**result;

// 	show_func(__func__, MY_START, NULL);
// 	// Encontrar o número total de segmentos
// 	i = 0;
// 	count = 0;
// 	while (path[i] != NULL)
// 	{
// 		current = path[i];
// 		while (*current != '\0')
// 		{
// 			if (*current == delimiter)
// 				count++;
// 			current++;
// 		}
// 		count++; // Contar o próprio segmento
// 		i++;
// 	}
// 	result = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	// Loop para dividir cada string no array original
// 	while (path[i] != NULL)
// 	{
// 		current = path[i];
// 		start = 0;
// 		// Encontrar segmentos na string atual
// 		while (*current != '\0')
// 		{
// 			if (*current == delimiter)
// 			{
// 				result[j] = ft_strdup(path[i] + start);
// 				if (result[j] == NULL)
// 					return (NULL);
// 				j++;
// 				start = current - path[i] + 1;
// 			}
// 			current++;
// 		}
// 		// Adiciona o último segmento
// 		result[j] = ft_strdup(path[i] + start);
// 		if (result[j] == NULL)
// 			return (NULL);
// 		j++;
// 		i++;
// 	}
// 	// Adiciona NULL para indicar o final do novo array
// 	result[j] = NULL;
// 	show_func(__func__, SUCCESS, NULL);
// 	return (result);
// }
