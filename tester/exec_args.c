/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:13:01 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/22 01:12:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

/// @brief 			Execute the command
/// @param parsed	Pointer to the command to be executed
void exec_args(char **parsed)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return (ERROR);
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command..");
			exit(0);
		}
		else
			wait(NULL);
	}
	return (SUCCESS);
}

// Function where the piped system commands is executed
// pipefd[0] is read end, pipefd[1] is write end
// write(pipefd[1], anymsg, strlen(arr) + 1);
// read(pipefd[0], anybuff, sizeof(anybuff));

/// @brief 				Execute 2 piped the command with pipe
/// @param parsed		Pointer to the first command to be executed
/// @param parsedpipe	Pointer to the second command to be executed
void	exec_args_piped(char **parsed, char **parsedpipe)
{
	int pipefd[2];
	pid_t pid1;
	pid_t pid2;
	char *path;

	if (pipe(pipefd) < 0)
	{
		perror("\nPipe could not be initialized");
		return (ERROR);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("\nCould not fork");
		return (ERROR_FORK);
	}
	if (pid1 == 0)
	{
		// Child 1 executing..
		// It only needs to write at the write end
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		path = find_path(parsed[0]);
		/*execve if of type main(int argc, char **argv, char **envp)*/
		/* argv[argc] = NULL */
		/* meaning that:
		=> parsed[n] = NULL
		=> parsed[0] = cmd related to filenamed path
		=> envp an array of environement args*/
		if (execve(path, parsed[0], NULL) < 0)
		{
			perror("\nCould not execute command 1..");
			exit(0);
		}
	}
	else
	{
		// Parent executing
		pid2 = fork();
		if (pid2 < 0)
		{
			perror("\nCould not fork");
			return (ERROR_FORK);
		}
		// Child 2 executing..
		// It only needs to read at the read end
		if (pid2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			path = find_path(parsedpipe[0]);
			if (execve(path, parsedpipe[0], NULL) < 0)
			{
				perror("\nCould not execute command 2..");
				exit(0);
			}
		}
		else
		{
			// parent executing, waiting for two children
			wait(NULL);
			wait(NULL);
		}
	}
}


char *find_path(char *cmd)
{
	char *path;
	char **path_split;
	int i;

	i = -1;
	path = getenv("PATH");
	path_split = ft_split(path, ':');
	while (path_split[++i])
	{
		path_split[i] = ft_strjoin(path_split[i], "/");
		path_split[i] = ft_strjoin(path_split[i], cmd);
		if (access(path_split[i], F_OK) == 0)
			return (path_split[i]);
	}
	return (NULL);
}

// function for finding pipe

int parse_pipe(char *str, char **strpiped)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			break;
	}

	if (strpiped[1] == NULL)
		return 0; // returns zero if no pipe is found.
	else
	{
		return 1;
	}
}

// function for parsing command words
void parse_space(char *str, char **parsed)
{
	int i;

	i = -1;
	while (++i < MAXLIST)
	{
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}

int process_str(char *str, char **parsed, char **parsed_pipe)
{
	char *piped_str[2];
	int piped = 0;

	piped = parse_pipe(str, piped_str);

	if (piped)
	{
		parse_space(piped_str[0], parsed);
		parse_space(piped_str[1], parsed_pipe);
	}
	else
	{

		parseSpace(str, parsed);
	}

	if (ownCmdHandler(parsed))
		return 0;
	else
		return 1 + piped;
}
