/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/14 20:15:33 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*unset({"unset", "OLDPWD", NULL})
	char * p;
	fazer alteracao do OLDPWD e PWD com a funcao do antonio
	1o: OLDPWD = PWD;
	20: o PWD = getcwd(p, cd)
*/


/// @brief Remove a variable from the environment
/// @param arg Arguments passed to unset command
/// @param envp Current environment variables
/// @return Updated environment variables
char **unset_cmd(t_script *s)
{
    show_func(__func__, MY_START);
    int env_count = 0;

    // Count the number of environment variables
    while (s->envp && s->envp[env_count])
        env_count++;

    if (s->commands->argv[1] == NULL)
    {
        printf("Unset sem argumentos válidos\n");
        return s->envp;
    }

    // Allocate memory for the new environment array
    char **new_env = (char **)malloc(sizeof(char *) * (env_count + 1));
    if (!new_env)
        return NULL;

    int i = 0;
    int j = 0;

    // Copy the variables from the old environment to the new one,
    // excluding the one specified in the arguments
    while (i < env_count)
    {
        if (ft_strncmp(s->commands->argv[1], s->envp[i], ft_strlen(s->commands->argv[1])) != 0)
        {
            new_env[j] = ft_strdup(s->envp[i]);
            j++;
        }
        i++;
    }
    new_env[j] = NULL;
    return new_env;
}


// char **unset_cmd(char **arg, char **envp)
// {
//     show_func(__func__, MY_START);
//     int env_count = 0;

//     // Count the number of environment variables
//     while (envp && envp[env_count])
//         env_count++;

//     if (arg[1] == NULL)
//     {
//         printf("Unset sem argumentos válidos\n");
//         return envp;
//     }

//     // Allocate memory for the new environment array
//     char **new_env = (char **)malloc(sizeof(char *) * (env_count + 1));
//     if (!new_env)
//         return NULL;

//     int i = 0;
//     int j = 0;

//     // Copy the variables from the old environment to the new one,
//     // excluding the one specified in the arguments
//     while (i < env_count)
//     {
//         if (ft_strncmp(arg[1], envp[i], ft_strlen(arg[1])) != 0)
//         {
//             new_env[j] = ft_strdup(envp[i]);
//             j++;
//         }
//         i++;
//     }
//     new_env[j] = NULL;
//     return new_env;
// }
