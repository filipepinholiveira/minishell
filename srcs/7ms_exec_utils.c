/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:00:28 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/02 15:12:57 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
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
/// @param input_fd		O descritor de arquivo para a entrada padrão 
///                     (stdin) do processo filho. Pode ser STDIN_FILENO
///                     ou um descritor de arquivo de um pipe.
/// @param ouput_fd		O descritor de arquivo para a saída padrão (stdout)
///                     do processo filho. Pode ser STDOUT_FILENO
///                     ou um descritor de arquivo de um pipe.
void	execute_do_cmd(char **argv, char **envp, int input_fd, int output_fd)
{
	pid_t	child_pid;
	int		status;
	char	*cmd_path;
		// verificar o status se necessário
		// if (WIFEXITED(status)) {
		//     printf("Child process exited with status %d\n", 
		// 			WEXITSTATUS(status));
		// }
	show_func(__func__, MY_START);
	child_pid = fork();
	if (child_pid == -1) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0) 
	{
		// Processo filho
		if (input_fd != STDIN_FILENO) 
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO) 
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		cmd_path = get_location(argv[0]);
		execve(cmd_path, argv, envp);
		// Se o execve falhar
		perror ("execve");
		//Com essa informação, você poderá identificar se há
		/// algum problema com o caminho do executável 
		/// ou se o arquivo executável está ausente.
		exit(EXIT_FAILURE);
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
	show_func(__func__, SUCCESS);
}

/// @brief 		Executa dois comandos em sequência com um pipe entre eles.
/// @param s	Estrutura contendo informações sobre cmds a serem executados.
/// @param path_env		Array de strings representando o caminho do ambiente.
/// @return			0 em caso de sucesso, encerra o programa em caso de falha. 
int	pipex(t_script *s, char **path_env)
{
	int		pipe_fd[2];
	pid_t	child_pid;

	show_func(__func__, MY_START);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		// Processo filho
		close(pipe_fd[0]); // Fecha a extremidade de leitura do pipe
		// Redireciona stdout para a extremidade de escrita do pipe
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]); // Fecha a extremidade de escrita do pipe
		// Executa o primeiro comando
		execute_do_cmd(s->commands[0].argv, path_env, 
			STDIN_FILENO, pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else 
	{
		// Processo pai
		close(pipe_fd[1]); // Fecha a extremidade de escrita do pipe
		// Redireciona stdin para a extremidade de leitura do pipe
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]); // Fecha a extremidade de leitura do pipe
		// Executa o segundo comando
		execute_do_cmd(s->commands[1].argv, path_env, pipe_fd[0], 
			STDOUT_FILENO);
		// Aguarda o processo filho terminar
		wait(NULL);
	}
	show_func(__func__, SUCCESS);
	return (0);
}

/// @brief 			Splits a string into an array of strings using a delimiter.
/// @param path 		String to be splited
/// @param delimiter 	character used as delimiter
/// @return 			String array containing splited string
char	**split_path(char **path, char delimiter)
{
	size_t	count;
	size_t	i;
	size_t	j;
	size_t	start;
	char	*current;
	char	**result;

	show_func(__func__, MY_START);
	// Encontrar o número total de segmentos
	i = 0;
	count = 0;
	while (path[i] != NULL)
	{
		current = path[i];
		while (*current != '\0')
		{
			if (*current == delimiter)
				count++;
			current++;
		}
		count++; // Contar o próprio segmento
		i++;
	}
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	// Loop para dividir cada string no array original
	while (path[i] != NULL)
	{
		current = path[i];
		start = 0;
		// Encontrar segmentos na string atual
		while (*current != '\0')
		{
			if (*current == delimiter)
			{
				result[j] = strndup(path[i] + start, current - path[i] - start);
				if (result[j] == NULL)
					return (NULL);
				j++;
				start = current - path[i] + 1;
			}
			current++;
		}
		// Adiciona o último segmento
		result[j] = strdup(path[i] + start);
		if (result[j] == NULL)
			return (NULL);
		j++;
		i++;
	}
	// Adiciona NULL para indicar o final do novo array
	result[j] = NULL;
	show_func(__func__, SUCCESS);
	return (result);
}
