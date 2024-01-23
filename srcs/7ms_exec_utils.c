/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:00:28 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/24 12:57:51 by antoda-s         ###   ########.fr       */
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

static void	execute_do_cmd_1(t_script *s, int index)
{
	show_func(__func__, MY_START, s->commands->argv[index]);
	printf("envp: %s\n", s->envp[0]);

	//pid_t	fork_pid;
	char	**cmd_path;
	char	*exec_path;
	int i;

	i = -1;

	printf("FD in: %d  e FD out: %d no execute_do_cmd_1\n", s->fd[0], s->fd[1]);

	cmd_path = split_path(s->envp);
	if (cmd_path != NULL)
	{
		while (cmd_path[++i] != NULL)
		{
			exec_path = ft_strjoin(cmd_path[i], s->commands[index].argv[0]);
			if (!access(exec_path, F_OK))
			{
				printf("Break no acess do 1º cmd\n"); 
				printf("Cmd_path[%d]: %s\n", i, cmd_path[i]);
				break ;
			}
		}
	if (cmd_path[i])
	{
		printf("EXCVE vai executar %s\n", s->commands[index].argv[0]);
		close(s->fd[0]);
		printf("a partir daqui todos os printf do cmd_1 vao para s->fd[1]\n");
		dup2(s->fd[1], STDOUT_FILENO); // a partir daqui todos os printf vao para s->fd[1]!!!
		close(s->fd[1]);
		int status = execve(exec_path, s->commands[index].argv, NULL); // atençao que se entra no exec jao nao faz free!!! Filipe 17 jan
		if (status == -1)
		{
			//printf("erro no execve do cmd :%s\n", s->commands[index].argv[0]); STDOUT agora está no s->fd[1]!!!!
			perror("Error");
		}
	}
	free(exec_path);
	printf("%s: command not found\n", s->commands[index].argv[0]);
	exit(COMMAND_NOT_FOUND);
	}
}


static void execute_do_cmd_n(t_script *s, int index)
{
    show_func(__func__, MY_START, s->commands[index].argv[0]);
    printf("envp: %s\n", s->envp[0]);

    //pid_t fork_pid;
    char **cmd_path;
    char *exec_path;
    int i;

    i = -1;

	printf("FD in: %d  e FD out: %d no execute_do_cmd_n\n", s->fd[0], s->fd[1]);
	cmd_path = split_path(s->envp);
	if (cmd_path != NULL)
	{
		printf("CMD_path existe no last cmd\n");
		while (cmd_path[++i] != NULL)
		{
			exec_path = ft_strjoin(cmd_path[i], s->commands[index].argv[0]);
			if (!access(exec_path, F_OK))
			{
				printf("Break no acess do last cmd\n");
				printf("Cmd_path[%d]: %s\n", i, cmd_path[i]);
				break;
			}
		}
		if (cmd_path[i])
		{
			printf("EXCVE vai executar %s\n", s->commands[index].argv[0]);
			close(s->fd[1]);
			dup2(s->fd[0], STDIN_FILENO);
			close(s->fd[0]);
			int status = execve(exec_path, s->commands[index].argv, NULL);
			if (status == -1)
			{
				perror("Error");
			}
		}
		free(exec_path);
		printf("%s: command not found\n", s->commands[index].argv[0]);
		exit(COMMAND_NOT_FOUND);
	}
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
static void	execute_do_cmd_i(t_script *s, int index)
{
	show_func(__func__, MY_START, s->commands[index].argv[0]);
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
		printf("CMD_path existe no last cmd\n");
		while (cmd_path[++i] != NULL)
		{
			exec_path = ft_strjoin(cmd_path[i], s->commands[index].argv[0]);
			if (!access(exec_path, F_OK))
			{
				printf("Break no acess do last cmd\n");
				printf("Cmd_path[%d]: %s\n", i, cmd_path[i]);
				break;
			}
		}
		if (cmd_path[i])
		{
			printf("EXCVE vai executar %s\n", s->commands[index].argv[0]);
			dup2(s->fd[1], STDOUT_FILENO);
			dup2(s->fd[0], STDIN_FILENO);
			close(s->fd[1]);
			close(s->fd[0]);
			int status = execve(exec_path, s->commands[index].argv, NULL);
			if (status == -1)
			{
				perror("Error");
			}
		}
		free(exec_path);
		printf("%s: command not found\n", s->commands[index].argv[0]);
		exit(COMMAND_NOT_FOUND);
	}
}

/// @brief 		Executa dois comandos em sequência com um pipe entre eles.
/// @param s	Estrutura contendo informações sobre cmds a serem executados.
/// @param path_env		Array de strings representando o caminho do ambiente.
/// @return			0 em caso de sucesso, encerra o programa em caso de falha.
int pipex(t_script *s, char **path_env)
{
    show_func(__func__, MY_START, NULL);
    int cmd_num = s->cmd_count;
    //int fd[2];
	pid_t parent_pid;
    pid_t pids[cmd_num];
    int i;

    (void)path_env;


	printf("FD in: %d  e FD out: %d antes do	 pipe\n", s->fd[0], s->fd[1]);


    signal(SIGINT, sig_handler_fork); // tratamento de sinais

    i = 0;
    // while (++i < cmd_num - 1) // criação dos pipes
    // {
        if (pipe(s->fd) == -1)
        {
            perror("pipe");
            show_func(__func__, EXIT_FAILURE, NULL);
            exit(EXIT_FAILURE);
        }
    
	printf("FD in: %d  e FD out: %d criados pelo pipe\n", s->fd[0], s->fd[1]);
    i = -1;
    while (++i < cmd_num) // criação dos processos nos childs
    {
		parent_pid = getpid();
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
			//close(s->fd[0]); // se nao criamos o child, nao estaremos a fechar o fd do parent?
            //close(s->fd[1]); // a fd table no foi criado no child!
            show_func(__func__, ERROR, NULL);
            exit(EXIT_FAILURE);
        }
        else if (pids[i] == 0)
        {
            // entra no processo child

        	printf("Child nº %d criado para executar %s com o processo nº %d do parent %d\n", i + 1, s->commands[i].argv[0], pids[i], parent_pid);
            printf("total de processos: %d\n", cmd_num);
            
            if (i + 1 == 1)
            {
                // first command
				execute_do_cmd_1(s, i);
            }
            if (i + 1 == cmd_num)
            {
				// last command
                execute_do_cmd_n(s, i);
            }
			else
				// middle commands
				execute_do_cmd_i(s, i);
        }
			
		else if (pids[i] > 0)
		{
        	// parent process
			int k = -1;
			while (++k < cmd_num && errno != ECHILD)
			{
				printf("A aguardar pelo process: %d\n", pids[i]);
				printf("Valor do incremento i: %d\n", i);
				waitpid(pids[i], &g_exit_status, 0);
				if (WIFEXITED(g_exit_status))
				{
					g_exit_status = WEXITSTATUS(g_exit_status);
					printf("Child process %d exited with status %d\n", pids[i], g_exit_status);
					printf("Saiu do child nº %d com o processo %d\n", i + 1, pids[i]);
					break;
				}
			}
		}
    }
	close(s->fd[0]);
	close(s->fd[1]);
	
    show_func(__func__, SUCCESS, NULL);
    return (0);
}
