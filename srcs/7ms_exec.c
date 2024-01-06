/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/04 11:10:21 by fpinho-d         ###   ########.fr       */
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

int	execute_do(t_script *s)
{
	pid_t	child_pid;
	char	*cmd_path;

	show_func(__func__, MY_START, NULL);
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
	path_env = split_path(s->envp, ':');
	if (s->cmd_count == 1)
	{
		if (execute_do(s))
		{
			show_func(__func__, SUCCESS, NULL);
			return (1);
		}
	}
	else
		if (pipex(s, path_env))
			return (1);
	//execute_do(s);
	//termios_setter(&s->termios_p);
	show_func(__func__, SUCCESS, NULL);
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
		else if (chil	// t_token	*tmp;

	// tmp = head;
	show_func(__func__, MY_START, NULL);
	if (head && head->type == TOKEN_PIPE)
		return (return_error("Syntax error", 0));
	while (head)
	{
		if (!head->next && (head->type == TOKEN_PIPE
				|| head->type == TOKEN_R_IN
				|| head->type == TOKEN_R_OUT))
			return (return_error("Syntax error", 0));
		if (head->type == TOKEN_PIPE && head->next
			&& head->next->type == TOKEN_PIPE)
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
		if (head->type == TOKEN_PIPE)
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
		while (head && head->type != TOKEN_PIPE)
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
		while (head && head->type != TOKEN_PIPE)
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
