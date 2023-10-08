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

void    ft_execmd (char **Token_list)
{
    char *command = NULL;

    if (Token_list && Token_list[0])
    {
        //printf("entra no execmd\n");
        //printf("%s\n", Token_list[0]);
        command = Token_list[1];
        if (execve(command, Token_list, NULL) == -1)
            perror("Error:\n");

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