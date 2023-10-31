/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 03:21:19 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/10/08 07:29:06 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* a funçao tokenize vai receber uma string com o input do utilizador, e vai ter que calcular
quantas palavras recebeu o input, separa-las por tipo (command, built in, pipe, special char, et),
para serem tratadas ou executadas*/

/* a funçao tokenize vai receber uma string com o input do utilizador, e vai ter que calcular
quantas palavras recebeu o input, separa-las por tipo (command, built in, pipe, special char, et),
para serem tratadas ou executadas*/

#include "minishell.h"

char *    ft_tokenize(const char *input, char **av, size_t *nbr_tokens)
{
    size_t tokens_nbr = 0; // conar os tokens
    size_t i = 0;
    size_t j = 0;
    char * input_copy = NULL; // para copiar a string a usar no strtok e identificar tokens
    input_copy = malloc (sizeof(char) * ft_strlen(input) + 1);
    char *Token_list = NULL; // para criar os tokens

    (void) nbr_tokens;
    //ft_strlcpy(Token_list, av[0], ft_strlen(av[0]) + 1);
    ft_strlcpy(input_copy, (char *) input, ft_strlen(input) + 1); // copiar a string a usar no strtok e identificar tokens
    
    //printf("input no inicio: %s\n", input);
    char *token = ft_strtok((char *)input, " "); // identifica e cria o primeiro token 
    //printf("input apos strtok: %s\n", input);
    //printf("\n\nAV[0] recebido:%s\n", av[0]);

    while (token != NULL) // conto o numero de tokens
    {
        //printf("Token_list no lopp: %s\n", token);
        tokens_nbr++;
        token = ft_strtok(NULL, " ");
    }
    Token_list = malloc (sizeof(char) * ft_strlen(av[0]) + 1);
    ft_strlcpy(Token_list, av[0], ft_strlen(av[0]) + 1);
    av = malloc (sizeof(char) * tokens_nbr + 1); // crio memoria para o numero de pointers necessarios
    if (!av)
        return (printf("Erro alocar memoria av no ft_tokanize\n"), NULL);    
    //av[i] = malloc (sizeof(char) * ft_strlen(Token_list) + 1);
    token = ft_strtok(input_copy, " "); //volto a criar e identificar o primeiro token ca string copiada
    //printf("Token[%ld] %s\n", i, av[i]);

    while (i < tokens_nbr && token != NULL)
    {
        // if (i == 0)
        // {
        //     ft_strlcpy(av[i], Token_list, ft_strlen(Token_list) + 1);
        //     //printf("Token[%ld] %s\n", i, av[i]);
        //     i++;
        // }
        // else
        {
            av[i] = malloc (sizeof(char) * ft_strlen(token) + 1);
            if (av[i] == NULL)
                return (printf("Erro alocar memoria av[i] no ft_tokanize\n"), NULL);
            ft_strlcpy(av[i], token, ft_strlen(token) + 1);
            token = ft_strtok(NULL, " ");
            //printf("Token[%ld] %s\n", i, av[i]);
            i++;
        }
    }
    av[i] = NULL;

    

    // printf("\nApós o loops:\n\n");
    // printf("numero de tokens: %ld\n", tokens_nbr);
    // printf("\nVerificaçao dos tokens:\n");
    while(j <= tokens_nbr)
    {
        //printf("Token[%ld]: %s\n", j, av[j]);
        j++;
    }
    j--;
    
    ft_execmd(av, tokens_nbr);

    // while (j > 0)
    // {
    //     if (av[j] != NULL)
    //         free(av[j]);
    //     j--;
    // }
    //free(Token_list[j]);
    //free(Token_list);
    free(input_copy);
    //printf("input no fim: %s\n", input);
    //printf("Token_list: %s\n", token);
    //*nbr_tokens = tokens_nbr;
    //tokens_nbr = 0;
    return (token);
}