/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 23:55:20 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/11/15 17:46:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_execmd(char **Token_list, int tokens_nbr)
{
        int i = 0;
        (void) tokens_nbr;

        //printf("Numero de tokens é: %d\n", tokens_nbr);

        if (strcmp(Token_list[i], "cd") == 0)
        {
            cd_command(Token_list);
            //printf("executar executavel cd\n");
            wait(NULL);
//         // Lidar com o comando "ls" diretamente, por exemplo, chamando uma função personalizada para listar diretórios.
//     } else if (strcmp(Token_list[0], "cd") == 0) {
//         // Lidar com o comando "cd" diretamente, por exemplo, chamando chdir() para mudar o diretório.
		}
        else
        {
            pid_t child_pid = fork();

            if (child_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (child_pid == 0)
            {
                // Processo filho
                char *command = get_location(Token_list[i]);
                if (command != NULL) {
                    if (execve(command, Token_list, NULL) == -1) {
                        perror("Error");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    // Tratar comandos que não existem no caminho especificado
                    printf("Comando não encontrado: %s\n", Token_list[i]);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                // Processo pai
                wait(NULL);
            }
            i++;
        }
}
