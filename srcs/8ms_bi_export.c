/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/14 19:48:14 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/// @brief          add new environment variable to env
/// @param arg      new env variable to add 
/// @param envp      environment variables lis 
/// @return         the new env variables
/// STILL TESTING 
char    **export_cmd(char **arg, char **envp)
{   
    show_func(__func__, MY_START);

    int count;

    count = arg_count(arg);

    // Se não houver argumentos ou o argumento não contiver '=', retorna o ambiente existente
    if (count == 1 || !ft_strrchr(arg[1], (int)'='))
    {
        show_func(__func__, SUCCESS);
        printf("Export sem argumentos válidos\n"); // Indicação apenas para teste, não aparece no shell
        return envp;
    }

    // Aloca memória para o novo array de strings
    char **new_env = (char **)malloc(sizeof(char *) * (count + env_count(envp) + 1));

    if (!new_env)
    {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }

    int i = 0;

    // Copia as variáveis de ambiente existentes para o novo array
    while (envp[i])
    {
        new_env[i] = ft_strdup(envp[i]);
        i++;
    }

    // Adiciona as novas variáveis de ambiente ao novo array
    int j = 1;
    while (j < count)
    {
        new_env[i] = ft_strdup(arg[j]);
        i++;
        j++;
    }

    new_env[i] = NULL; // Define a última entrada como NULL para indicar o fim do array

    show_func(__func__, SUCCESS);
    return new_env;
}

















// char    **export_cmd(char **arg, char **envp)
// {   
//     show_func(__func__, MY_START);
//     char    **new_env;
//     int     count;
//     int     i;

//     count = arg_count(arg);
//     printf("Numero de args: %i\n", count);
//     if (count == 1 || !ft_strrchr(arg[1], (int)'='))
//     {
//         printf("Export sem argumentos válidos\n"); // indicaçao apenas para teste, nao surge no shell
//         return(envp);
//     }
//     new_env = (char **)malloc(sizeof(char *) * (count + 1));
//     if (!new_env)
//         return (NULL);
//     i = 0;
    
//     while (i < count)
//     {
//         if (arg[i + 1])
//             new_env[i] = ft_strdup(arg[i + 1]);
//         else
//             new_env[i] = NULL; // Evita ft_strdup(NULL)
//         i++;
//     }
//     new_env[count] = NULL;
//     return (new_env);
// }