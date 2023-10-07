/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 03:21:19 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/10/07 16:54:59 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* a funçao tokenize vai receber uma string com o input do utilizador, e vai ter que calcular
quantas palavras recebeu o input, separa-las por tipo (command, built in, pipe, special char, et),
para serem tratadas ou executadas*/

#include "minishell.h"

char *    ft_tokenize(const char *input, char **av, size_t *nbr_tokens)
{
    size_t tokens_nbr = *nbr_tokens;
    size_t i = 0;
    char * input_copy = NULL;
    input_copy = malloc (sizeof(char) * ft_strlen(input) + 1);
    char *av_path = NULL;
    av_path = malloc (sizeof(char) * ft_strlen(av[0]) + 1);

    ft_strlcpy(av_path, av[0], ft_strlen(av[0]) + 1);
    ft_strlcpy(input_copy, (char *) input, ft_strlen(input) + 1);
    
    //printf("input no inicio: %s\n", input);
    char *token = ft_strtok((char *)input, " "); // nao podemos usar strtok no projeto, temos que fazer o nosso
    //printf("input apos strtok: %s\n", input);
    printf("av_path:%s\n", av_path);

    while (token != NULL)
    {
        printf("Token no lopp: %s\n", token);
        tokens_nbr++;
        token = ft_strtok(NULL, " ");
    }
    av = malloc (sizeof(char) * tokens_nbr + 1);
    if (!av)
        return (printf("Erro alocar memoria av no ft_tokanize\n"), NULL);    
    token = ft_strtok(input_copy, " ");
    while (i <= tokens_nbr && token != NULL)
    {
        if (i == 0)
        {
            av[i] = malloc (sizeof(char) * ft_strlen(av_path) + 1);
            ft_strlcpy(av[0], av_path, ft_strlen(av_path) + 1);
        }
        else
        {
            av[i] = malloc (sizeof(char) * ft_strlen(token) + 1);
            if (av[i] == NULL)
                return (printf("Erro alocar memoria av[i] no ft_tokanize\n"), NULL);
            ft_strlcpy(av[i], token, ft_strlen(token) + 1);
        }
        printf("o que copiei para av %ld: %s\n", i, av[i]);
        if (i != 0)
            token = ft_strtok(NULL, " ");
        i++;
    }
    printf("numero de tokens: %ld\n", tokens_nbr);
    i = 0;
    printf("av[0]:%s\n", av[0]);
    while(i <= tokens_nbr)
    {
        printf("Token %ld: %s\n", i, av[i]);
        i++;
    }
    i = 0;
    // while(i <= tokens_nbr && av)
    // {
    //     free(av[i]);
    //     i++;
    // }
    //free(av);
    // free(av_path);
    // free(input_copy);
    //printf("input no fim: %s\n", input);
    //printf("Token: %s\n", token);
    //*nbr_tokens = tokens_nbr;
    //tokens_nbr = 0;
    return (token);
}