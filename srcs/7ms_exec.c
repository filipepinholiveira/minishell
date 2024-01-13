/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/15 10:42:50 by antoda-s         ###   ########.fr       */
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
		if (!ft_strncmp(bi_cmd[i].bi_cmd, s->commands[n].argv[0],
				ft_strlen(bi_cmd[i].bi_cmd)))
		{
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
				status = execve(exec_path, s->commands[n].argv, NULL);
				free (exec_path);
				if (status)
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
		waitpid(fork_pid, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
		{
		    g_exit_status = WEXITSTATUS(g_exit_status);
			printf("Child process exited with status %d\n", g_exit_status);
		}
		printf("Saiu do child\n)");
	}
	return (0);
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
	else if(s->commands[0].out.name)
	{
		printf("Temos que executar %s e enviar para %s\n", s->commands[0].argv[0], s->commands[0].out.name);
		/*
		echo filipe > f.txt > g.txt > j.txt
		qq coisa como while (s->commands[0].argv[i])
		{
			contar o numero de >, e fazer pipes, escrever (fd1) o valor de cmd echo, e ler 
			no ficheiro criado "f.txt" (fd0), escrevendo (fd1), lendo (fd) no g.txt, escrevendo (fd1)
			e lendo finalmente (fd0) j.txt
		}
		*/
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

/*

		if (strcmp(cmd[0], "echo") == 0)
			bi_echo_print(cmd); // FEITO???
		else if (strcmp(cmd[0], "cd") == 0)
			bi_cd(cmd); // FEITO
		else if (strcmp(cmd[0], "pwd") == 0)
		{
			bi_pwd(); // FEITO???
		}
		else if (strcmp(cmd[0], "export") == 0)
			printf("Execute export with no options\n");
		else if (strcmp(cmd[0], "unset") == 0)
			printf("Execute unset with no options\n");
		else if (strcmp(cmd[0], "env") == 0)
		{
			bi_env(cmd, envp); // FEITO
		}
		else if (strcmp(cmd[0], "exit") == 0)
		{
				bi_exit(cmd); // FEITO
		}
		else
			{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (chil	// t_token	*tmp;

	// tmp = head;
	show_func(__func__, MY_START, NULL);
	if (head && head->type == T_PIPE)
		return (return_error("Syntax error", 0));
	while (head)
	{
		if (!head->next && (head->type == T_PIPE
				|| head->type == TOKEN_R_IN
				|| head->type == TOKEN_R_OUT))
			return (return_error("Syntax error", 0));
		if (head->type == T_PIPE && head->next
			&& head->next->type == T_PIPE)
			return (return_error("Syntax error", 0));
		if ((head->type == TOKEN_R_OUT || head->type == TOKEN_R_IN)
			&& (head->next && head->next->type != TOKEN_NAME))
			return (return_error("Syntax error", 0));
		head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

/// @brief			This function simply counts the number of pipes in our
///					linked list of tokens to determine the number of chained
///					commands are in the line buffer.
/// @param head		Head of the token list
/// @return			Number of commands
int	get_cmd_count(t_token *head)
{
	show_func(__func__, MY_START, NULL);
	int	count;

	count = 0;
	while (head)
	{
		if (!count)
			count = 1;
		if (head->type == T_PIPE)
			count ++;
		head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (count);
}

/// @brief		This function simply trims the leading and trailing whitespace
///				that can be found when replacing an environment variable.
/// @param head	Head of the token list
/// @return		Trimmed content
void	trim_spaces(t_token *head)
{
	char	*tmp;

	show_func(__func__, MY_START, NULL);
	while (head)
	{
	// if (s)
	// 	printf("s token = %s\n", s);
	// else
	// 	printf("s is empry\n");
		tmp = head->content;
		head->content = ft_strtrim(tmp, " \t\v\r\n\f");
		free(tmp);
		head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief			This function determines the amount of arguments each command
///					has so the argv can be malloced to the right size in the
///					following steps.
/// @param head		Head of the token list
/// @param script	Script pointer
/// @return			Trimmed content
void	get_num_args(t_token *head, t_script *script)
{
	t_token	*tmp;
	int		i;

	show_func(__func__, MY_START, NULL);
	i = 0;
	while (i < script->cmd_count)
	// if (s)
	// 	printf("s token = %s\n", s);
	// else
	// 	printf("s is empry\n");
	{
		script->commands[i].argc = 0;
		tmp = head;
		while (head && head->type != T_PIPE)
		{
			if (head->type == TOKEN_NAME && (tmp->type != TOKEN_R_IN
					&& tmp->type != TOKEN_R_OUT))
				script->commands[i].argc++;
			tmp = head;
			head = head->next;
		}
		if (head)
			head = head->next;
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief 			Iniatilzes file names direction and remove quotes from names
/// @param commands Struct witj info about files
/// @param max 		max number of files
/// @param head 	pointert o command struct hed
void	set_filenames_null(t_command *commands, int max, t_token *head)
{
	int	i;

	show_func(__func__, MY_START, NULL);
	i = -1;
	while (++i < max)
	{
		commands[i].in.name = NULL;
		commands[i].out.name = NULL;
		commands[i].in.heredoc = NULL;
	}
	while (head)
	{
		head->content = remove_quotes(head->content);
		head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief 		This function iterates through a linked list of tokens and
///				fills the command structure based on the type of token it
///				encounters.
/// @param head	Head of the token list
/// @param cmd	Command structure
/// @param i	Index
/// @param j	Index
/// @return		0 if success, 1 if failure
int	parse_commands(t_token *head, t_command *cmd, int i, int j)
{
	show_func(__func__, MY_START, NULL);
	while (head)
	{
		cmd[i].argv = malloc(sizeof(char *) * (cmd[i].argc + 1));
		if (!cmd[i].argv)
		{
			show_func(__func__, ERROR, NULL);
			return (1);
		}
		j = 0;
		while (head && head->type != T_PIPE)
		{
			if (head->type == TOKEN_NAME)
				cmd[i].argv[j++] = ft_strdup(head->content);
			else if (head->type == TOKEN_R_IN && redir(head, &cmd[i].in))
			{
				printf("%s : exit 01\n", __func__);
				show_func(__func__, SUCCESS, NULL);
				return (free_commands(cmd, i + 1));
			}
			else if (head->type == TOKEN_R_OUT && redir(head, &cmd[i].out))
			{
				printf("%s : exit 02\n", __func__);
				show_func(__func__, SUCCESS, NULL);
				return (free_commands(cmd, i + 1));
			}
			if (head->type == TOKEN_R_IN || head->type == TOKEN_R_OUT)
				head = head->next;
			if (head)
				head = head->next;
		}
		if (head)
			head = head->next;
		cmd[i].argv[j] = NULL;
		i++;
	}
	printf("%s : exit 03\n", __func__);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

/// @brief 			This function sets the open flags and opens the files
///					based on the type of redirection token it encounters
///					('<', '<<', '>', '>>').
/// @param head		Head of the token list
/// @param file		Redirection file structure
/// @return			0 if success, 1 if failure
int	redir(t_token *head, t_redirection *file)
{
	int		ret;

	show_func(__func__, MY_START, NULL);
	if (file->name)
		free(file->name);
	if (!head->next || head->next->type != TOKEN_NAME)
		return (0);
	file->name = ft_strdup(head->next->content);
	if (!ft_strncmp(head->content, ">>", 2))
		file->flag = (O_CREAT | O_APPEND | O_RDWR);
	else if (!ft_strncmp(head->content, "<<", 2))
		fill_heredoc(file);
	else if (!ft_strncmp(head->content, ">", 1))
		file->flag = (O_CREAT | O_TRUNC | O_RDWR);
	else if (!ft_strncmp(head->content, "<", 1))
		file->flag = O_RDONLY;
	if (file->flag == -1)
		return (0);
	ret = open(file->name, file->flag, 0644);
	if (ret == -1)
		return (return_error(file->name, 1));
	close(ret);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}d_pid == 0)
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
