/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/29 00:21:50 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>


// int parse_shell(char **cmdline)
// {
// 	while (*cmdline != NULL)
// 	{
// 		if (invalid_quotes(cmdline))
// 			return (ERROR);
// 		*cmdline = ft_tokenize(*cmdline);
// 	}
// }


//static init_all(char **)
// int	main(int argc, char **argv)
// {
// 	if (invalid_argc(argc) || invalid_argv(argv))
// 		return (ERROR);
// 	return (init_all(argv));
// }


int	main(int argc, char **argv)
{
	char		*prompt = "(Versao teste $) >";
	char		*line = NULL;
	// const char	*exit_shell = "exit";
	// size_t		nbr_tokens = 0;
	//t_cmd		pcmd;

	(void)argc;
	(void)argv;

	while (1)
	{
		printf("%s", prompt);
		line = readline(line);
		if (line == NULL)
		{
			printf("Exiting shell...\n");
			free ((char *)line);
			return (-1);
		}
		if (invalid_line(line))
		{
			show_func(__func__, ERROR);
		}
		line = trimmer(line, " \t\v\r\n\f");
		if (line)
			printf("\t%s : line :%s\n",__func__, line);
		free(line);
	}
	return (0);
}

// void continue_main_here(void)
// {
// 	//	init_shell();
// 	while (1)
// 	{
// 		printf("%s", prompt);
// 		lineptr = readline(lineptr);
// 		if (lineptr == NULL)
// 		{
// 			printf("Exiting shell...\n");
// 			free ((char *)lineptr);
// 			return (-1);
// 		}
// 		else if (ft_strncmp(lineptr, exit_shell, ft_strlen(exit_shell)) == 0) //tratamento temporario do exit, ja que exit é um command a ser executado e nao
// 		{
// 			printf("Exiting shell...\n");
// 			free ((char *)lineptr);
// 			return (-1);
// 		}
// 		while(lineptr != NULL)
// 		{
// 			lineptr = ft_tokenize(lineptr, &nbr_tokens);
// 		}
// 	}
// 	free((char *)lineptr);
// 	free((char *) exit_shell);
// 	return (0);
// }
