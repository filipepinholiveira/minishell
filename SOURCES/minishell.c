/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:31:02 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/10/07 15:57:17 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
    // char *readline (const char *prompt);

    (void) ac;

    char *prompt = "(Shell do Antonio e do Filipe $) > ";
    const char *lineptr = NULL;
    //const char *linptr_cpy = NULL;
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
        nbr_tokens = 0;
    }
    free ((char *)lineptr);
    return (0);
}