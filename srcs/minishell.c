/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/27 18:24:01 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


int	invalid_argc(int argc)
{
	if (argc != 1)
	{
		printf("Invalid number of arguments\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int invalid_argv(char **argv)
{


	if (argv[0] == NULL)
	{
		printf("Invalid argument\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int invalid_quotes(char **cmdline)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (cmdline[i] != NULL)
	{
		while (cmdline[i][j] != '\0')
		{
			if (cmdline[i][j] == '\"')
				k++;
			j++;
		}
		if (k % 2 != 0)
		{
			printf("Invalid quotes\n");
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int parse_shell(char **cmdline)
{
	while (*cmdline != NULL)
	{
		if (invalid_quotes(cmdline))
			return (ERROR);
		*cmdline = ft_tokenize(*cmdline);
	}
}


//static init_all(char **)



// int	main(int argc, char **argv)
// {
// 	if (invalid_argc(argc) || invalid_argv(argv))
// 		return (ERROR);
// 	return (init_all(argv));
// }


int	main(int argc, char **argv)
{
	char		*prompt = "(Versao teste $) > ";
	char		*lineptr = NULL;
	const char	*exit_shell = "exit";
	size_t		nbr_tokens = 0;
	//t_cmd		pcmd;

//	(void)ac;
//	(void)av;

	if (argc != 1)
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}

	if (invalid_argv(++argv))
		return (ERROR);
	else
		printf("Valid arguments\n");
	return (0);
}

void continue_main_here(void)
{
	//	init_shell();
	while (1)
	{
		printf("%s", prompt);
		lineptr = readline(lineptr);
		if (lineptr == NULL)
		{
			printf("Exiting shell...\n");
			free ((char *)lineptr);
			return (-1);
		}
		else if (ft_strncmp(lineptr, exit_shell, ft_strlen(exit_shell)) == 0) //tratamento temporario do exit, ja que exit é um command a ser executado e nao
		{
			printf("Exiting shell...\n");
			free ((char *)lineptr);
			return (-1);
		}
		while(lineptr != NULL)
		{
			lineptr = ft_tokenize(lineptr, &nbr_tokens);
		}
	}
	free((char *)lineptr);
	free((char *) exit_shell);
	return (0);
}
