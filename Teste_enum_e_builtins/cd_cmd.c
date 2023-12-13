/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:46 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/06 14:39:09 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../SOURCES/minishell.h"


int arg_count(char **cmd)
{
    int count = 0;
    while (cmd[count])
        count++;
    return (count);
}


int cd_cmd(char **args) 
{
    int count = arg_count(args);
    if (count > 2)
    {
        printf("Minishell: cd: too many arguments\n");
            return 1;
    }
    if (args[1] == NULL)
    {
        // Nenhum diretório fornecido, volte para o diretório inicial do usuário.
        char *home = getenv("HOME");
        if (home == NULL) 
        {
            perror("Minishell: cd");
            return 1;
        }
        if (chdir(home) != 0) 
        {
            perror("Minishell: cd");
            return 1;
        }
    } 
    else 
    {
        if (chdir(args[1]) != 0) 
        {
            perror("Minishell: cd");
            return 1;
        }
    }
    return 0;
}
