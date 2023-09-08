/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 03:21:19 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/09/08 05:53:28 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* a funçao tokenize vai receber uma string com o input do utilizador, e vai ter que calcular
quantas palavras recebeu o input, separa-las por tipo (command, built in, pipe, special char, et),
para serem tratadas ou executadas*/

#include "minishell.h"

void    ft_tokenize(char *input, char **av)
{
    size_t nbr_tokens = 0;
    printf("input que entra tokanize inicio: %s\n", input);
    char *token = strtok(input, " ");
    printf("input apos strtok: %s\n", input);
    while (token != NULL)
    {
        nbr_tokens++;
        token = strtok(NULL, " ");
    }
    free(token);
    (void) av;
    printf("numero de tokens: %ld\n", nbr_tokens);
    printf("input que sai tokanize fim: %s\n", input);
}