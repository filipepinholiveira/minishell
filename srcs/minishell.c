/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/25 17:33:14 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av)
{
	char		*prompt = "(Versao teste $) > ";
	char		*lineptr = NULL;
	const char	*exit_shell = "exit";
	size_t		nbr_tokens = 0;

	(void)ac;
	(void)av;
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
