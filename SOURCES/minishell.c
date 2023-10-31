/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:31:02 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/10/08 06:59:16 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
    // char *readline (const char *prompt);

    (void) ac;

    char *prompt = "(Versao teste $) > ";
    const char *lineptr = NULL;
    const char *exit_shell = "exit";
    size_t nbr_tokens = 0;
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