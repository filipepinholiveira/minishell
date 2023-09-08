/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:31:02 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/09/08 05:37:41 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
    // ssize_t getline(char **lineptr, size_t *n, FILE *stream);

    (void) ac;
    (void) av;

    char *prompt = "(Shell do Antonio e do Filipe $) > ";
    char *lineptr = NULL;
    char *linptr_cpy = NULL;
    char *exit_shell = "exit";
    size_t nchars_read = 0;
    size_t n = 0;

    while (1)
    {
        printf("%s", prompt);
        nchars_read = getline(&lineptr, &n, stdin); // no minishell tenho que usar a readline!!!!!!!!!!!!!1
        if (nchars_read == (size_t) -1) // check if the getline function failed or reached EOF or user use CTRL + D
        {
            printf("Exiting shell...\n");
            free (lineptr);
            return (-1);
        }
        else if (strcmp(lineptr, exit_shell) == 10) //tratamento temporario do exit, ja que exit é um command a ser executado e nao
        {
            printf("Exiting shell...\n");
            free (lineptr);
            return (-1);
        }
        printf("Input: %s", lineptr);
        linptr_cpy = malloc(sizeof (char) * nchars_read);
        if (!linptr_cpy)
            return(printf("erro malloc"), 1);
        linptr_cpy = strcpy(linptr_cpy, lineptr);
        ft_tokenize(linptr_cpy, av);
    }
    free (lineptr);
    return (0);
}