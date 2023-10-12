/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 23:55:20 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/10/08 07:29:09 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_execmd (char **Token_list, int tokens_nbr)
{
    char *command = NULL;
    char *actual_command = NULL;

    int i = 1;

    if (Token_list && Token_list[0])
    {
        //printf("entra no execmd\n");
        //printf("%s\n", Token_list[0]);
        while (i <= tokens_nbr)
        {
            command = Token_list[i];
            actual_command = get_location(command);
            if (execve(actual_command, Token_list, NULL) == -1)
                perror("Error:\n");
            i++;
        }

    }

}





// void    ft_execmd (char **Token_list)
// {
//     printf("entra no execmd\n");
//     char *command;
//     int result;
//     if (Token_list && Token_list[0])
//     {
//         char * exec_path = "../bin/ls";
//         command = malloc (sizeof(char) * (ft_strlen(exec_path) + 1));
//         ft_strlcpy(command, exec_path, (ft_strlen(exec_path) + 1));
//         printf("command: %s\n\n", command);
//         printf("meio no execmd\n");
//         result = execve(command, Token_list, NULL);
//         printf("result:%d\n", result);
//         if (result == -1)
//         {
//             perror("Erro na execução do programa");
//         }
//         else
//             printf("comando pronto para ser executado\n");
//     }
// }