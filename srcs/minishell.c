/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/17 19:33:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av)
{
	char		*prompt = "(Versao teste $) > ";
	char	*lineptr = NULL;
	const char	*exit_shell = "exit";
	size_t		nbr_tokens = 0;
	// char *readline (const char *prompt);

	(void)ac;
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
			lineptr = ft_tokenize(lineptr, av, &nbr_tokens);
		}
	}
	free ((char *)lineptr);
	free((char *) exit_shell);
	return (0);
}
