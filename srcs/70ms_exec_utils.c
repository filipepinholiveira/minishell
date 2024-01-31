/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   70ms_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:00:28 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/31 13:00:04 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int first_child(t_script *s, int n)
{
	show_func(__func__, MY_START, s->cmds->argv[n]);
	exec_one(s, n);
		show_func(__func__, SUCCESS, NULL);
	return (0);
}
static int	execute_do_cmd_1(t_script *s, int n)
{
	show_func(__func__, MY_START, s->cmds->argv[n]);
	printf("envp: %s\n", s->envp[0]);

	pid_t	pid;
	//char	**cmd_path;
	//char	*exec_path; // ?????
	//int 	i;
	//int		status;
	//int 	p[2];


	//i = -1;
	printf("FD in: %d  e FD out: %d no execute_do_cmd_1\n", s->fd[0], s->fd[1]);
	if (pipe(s->fd) == -1)
	{
		perror("pipe");
		show_func(__func__, EXIT_FAILURE, NULL);
		exit(EXIT_FAILURE);
	}
	printf("FD in: %d  e FD out: %d no execute_do_cmd_1\n", s->fd[0], s->fd[1]);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		show_func(__func__, EXIT_FAILURE, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		//cmd_path = split_path(s->envp);
		first_child(s, n);
		close (s->fd[1]);
	}
		show_func(__func__, SUCCESS, NULL);
	return (0);
}






// 		if (cmd_path != NULL)
// 		{
// 			while (cmd_path[++i] != NULL)
// 			{
// 				exec_path = ft_strjoin(cmd_path[i], s->cmds[n].argv[0]);
// 				if (!access(exec_path, F_OK))
// 				{
// 					printf("Break : 1st command path found\n");
// 					printf("Cmd_path[%d]: %s\n", i, cmd_path[i]);
// 					break ;
// 				}
// 			}
// 			if (cmd_path[i])
// 			{
// 				printf("EXCVE vai executar %s\n", s->cmds[n].argv[0]);
// 				close(s->fd[0]);
// 				printf("a partir daqui todos os printf do cmd_1 vao para s->fd[1]\n");
// 				dup2(s->fd[1], STDOUT_FILENO); // a partir daqui todos os printf vao para s->fd[1]!!!
// 				close(s->fd[1]);
// 				status = execve(exec_path, s->cmds[n].argv, NULL); // atençao que se entra no exec jao nao faz free!!! Filipe 17 jan
// 				if (status == -1)
// 				{
// 					//printf("erro no execve do cmd :%s\n", s->cmds[index].argv[0]); STDOUT agora está no s->fd[1]!!!!
// 					perror("Error");
// 				}
// 			}
// 		free(exec_path);
// 		printf("%s: command not found\n", s->cmds[n].argv[0]);
// 		exit(COMMAND_NOT_FOUND);
// 		}
// 	}
// 	else if (pid > 0)
// 	{



// 	cmd_path = split_path(s->envp);
// 	if (cmd_path != NULL)
// 	{
// 		while (cmd_path[++i] != NULL)
// 		{
// 			exec_path = ft_strjoin(cmd_path[i], s->cmds[n].argv[0]);
// 			if (!access(exec_path, F_OK))
// 			{
// 				printf("Break : 1st command path found\n");
// 				printf("Cmd_path[%d]: %s\n", i, cmd_path[i]);
// 				break ;
// 			}
// 		}
// 		if (cmd_path[i])
// 		{
// 			printf("EXCVE vai executar %s\n", s->cmds[n].argv[0]);
// 			close(s->fd[0]);
// 			printf("a partir daqui todos os printf do cmd_1 vao para s->fd[1]\n");
// 			dup2(s->fd[1], STDOUT_FILENO); // a partir daqui todos os printf vao para s->fd[1]!!!
// 			close(s->fd[1]);
// 			status = execve(exec_path, s->cmds[n].argv, NULL); // atençao que se entra no exec jao nao faz free!!! Filipe 17 jan
// 			if (status == -1)
// 			{
// 				//printf("erro no execve do cmd :%s\n", s->cmds[index].argv[0]); STDOUT agora está no s->fd[1]!!!!
// 				perror("Error");
// 			}
// 	}
// 	free(exec_path);
// 	printf("%s: command not found\n", s->cmds[n].argv[0]);
// 	exit(COMMAND_NOT_FOUND);
// 	}
// }

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
static void	execute_do_cmd_i(t_script *s, int index)
{
	show_func(__func__, MY_START, s->cmds[index].argv[0]);
    printf("envp: %s\n", s->envp[0]);

    //pid_t fork_pid;
    char **cmd_path;
    char *exec_path;
    int i;

    i = -1;

	printf("FD in: %d  e FD out: %d no execute_do_cmd_i\n", s->fd[0], s->fd[1]);
	cmd_path = split_path(s->envp);
	if (cmd_path != NULL)
	{
		printf("CMD_path existe nos cmds intermedios\n");
		while (cmd_path[++i] != NULL)
		{
			exec_path = ft_strjoin(cmd_path[i], s->cmds[index].argv[0]);
			if (!access(exec_path, F_OK))
			{
				printf("Break no acess do cmd intermedio\n");
				printf("Cmd_path[%d]: %s\n", i, cmd_path[i]);
				break;
			}
		}
		if (cmd_path[i])
		{
			printf("EXCVE vai executar %s\n", s->cmds[index].argv[0]);
			printf("a partir daqui todos os printf do cmd_i vao para s->fd[1]\n");
			dup2(STDIN_FILENO, s->fd[0]);
			dup2(s->fd[1], STDOUT_FILENO);
			close(s->fd[0]);
			close(s->fd[1]);
			int status = execve(exec_path, s->cmds[index].argv, NULL);
			if (status == -1)
			{
				perror("Error");
			}
		}
		free(exec_path);
		printf("%s: command not found\n", s->cmds[index].argv[0]);
		exit(COMMAND_NOT_FOUND);
	}
}

static void execute_do_cmd_n(t_script *s, int index)
{
    show_func(__func__, MY_START, s->cmds[index].argv[0]);
    printf("envp: %s\n", s->envp[0]);

    //pid_t fork_pid;
    char **cmd_path;
    char *exec_path;
    int i;
	int	status;

    i = -1;

	printf("FD in: %d  e FD out: %d no execute_do_cmd_n\n", s->fd[0], s->fd[1]);
	cmd_path = split_path(s->envp);
	if (cmd_path != NULL)
	{
		//printf("CMD_path existe no last cmd\n");
		while (cmd_path[++i] != NULL)
		{
			exec_path = ft_strjoin(cmd_path[i], s->cmds[index].argv[0]);
			if (!access(exec_path, F_OK))
			{
				// printf("Break no acess do last cmd\n");
				// printf("Cmd_path[%d]: %s\n", i, cmd_path[i]);
				break;
			}
		}
		if (cmd_path[i])
		{
			printf("EXCVE vai executar %s\n", s->cmds[index].argv[0]);
			close(s->fd[1]);
			dup2(s->fd[0], STDIN_FILENO);
			close(s->fd[0]);
			status = execve(exec_path, s->cmds[index].argv, NULL);
			if (status == -1)
			{
				perror("Error");
			}
		}
		free(exec_path);
		printf("%s: command not found\n", s->cmds[index].argv[0]);
		exit(COMMAND_NOT_FOUND);
	}
}


/// @brief 		Executa dois comandos em sequência com um pipe entre eles.
/// @param s	Estrutura contendo informações sobre cmds a serem executados.
/// @param path_env		Array de strings representando o caminho do ambiente.
/// @return			0 em caso de sucesso, encerra o programa em caso de falha.
int	exec_many(t_script *s)
{
	show_func(__func__, MY_START, NULL);
	int i;

	signal(SIGINT, sig_handler_fork);
	i = -1;
	while (++i < s->cmd_count)
	{
		if (i + 1 == 1)
		{
			// first command
			execute_do_cmd_1(s, i);
		}
		else if (i + 1 == s->cmd_count)
		{
			// last command
			execute_do_cmd_n(s, i);
		}
		else
		{
			// middle cmds
			execute_do_cmd_i(s, i);
		}
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}



// int	exec_many(t_script *s, char **path_env)
// {
//     show_func(__func__, MY_START, NULL);
//     int cmd_num = s->cmd_count;
// 	//pid_t parent_pid;
//     //pid_t pids[cmd_num];
//     int i;

//     (void)path_env;

// 	//printf("%s : BEFORE PIPE : FD in: %d  e FD out: %d antes do pipe\n", __func__, s->fd[0], s->fd[1]);
//     signal(SIGINT, sig_handler_fork); // tratamento de sinais

//     //i = 0;
// 	// if (pipe(s->fd) == -1)
// 	// {
// 	// 	perror("pipe");
// 	// 	show_func(__func__, EXIT_FAILURE, NULL);
// 	// 	exit(EXIT_FAILURE);
// 	// }

// 	//printf("%s : AFTER PIPE : FD in: %d  e FD out: %d criados pelo pipe\n", __func__, s->fd[0], s->fd[1]);
//     i = -1;
//     while (++i < cmd_num) // criação dos processos nos childs
//     {
// 		//parent_pid = getpid();
//         //pids[i] = fork();
//         // if (pids[i] == -1)
//         // {
//         //     perror("fork");
// 		// 	//close(s->fd[0]); // se nao criamos o child, nao estaremos a fechar o fd do parent?
//         //     //close(s->fd[1]); // a fd table no foi criado no child!
//         //     show_func(__func__, ERROR, NULL);
//         //     exit(EXIT_FAILURE);
//         // }
//         // else if (pids[i] == 0)
//         // else if (pids[i] == 0)
//         // {
//         //     // entra no processo child

//         // 	printf("Child nº %d criado para executar %s com o processo nº %d do parent %d\n", i + 1, s->cmds[i].argv[0], pids[i], parent_pid);
//         //     printf("total de processos: %d\n", cmd_num);

//             if (i + 1 == 1)
//             {
//                 // first command
// 				execute_do_cmd_1(s, i);
//             }
//             else if (i + 1 == cmd_num)
//             {
// 				// last command
//                 execute_do_cmd_n(s, i);
//             }
// 			else
// 			{
// 				// middle cmds
// 				execute_do_cmd_i(s, i);
// 			}
//         }

// 		// else if (pids[i] > 0)
// 		// {
//         // 	// parent process
// 		// 	int k = -1;
// 		// 	while (++k < cmd_num || errno != ECHILD)
// 		// 	{
// 		// 		printf("PARENT MSG : a aguardar pelo process: %d\n", pids[i]);
// 		// 		printf("PARENT MSG :  command being executed %d\n", i + 1);
// 		// 		waitpid(pids[i], &g_exit_status, 0);
// 		// 		if (WIFEXITED(g_exit_status))
// 		// 		{
// 		// 			g_exit_status = WEXITSTATUS(g_exit_status);
// 		// 			printf("Child nº %d com o processo %d saiu normalmente com status %d\n", i + 1, pids[i], g_exit_status);
// 		// 			break;
// 		// 		}
// 		// 	}
// 		// }
//     }
// 	// close(s->fd[0]);
// 	// close(s->fd[1]);

//     show_func(__func__, SUCCESS, NULL);
//     return (0);
// }
