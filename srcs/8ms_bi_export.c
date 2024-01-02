/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/02 14:50:19 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// MINHA PRIMEIRA VERSAO

/// @brief          add new environment variable to env
/// @param arg      new env variable to add 
/// @param envp     environment variables lis 
/// @return         the new env variables
/// STILL TESTING 
// char    **export_cmd(char **arg, char **envp)
// {   
//     show_func(__func__, MY_START);

//     int count;

//     count = arg_count(arg);

//     // Se não houver argumentos ou o argumento não contiver '=', 
//retorna o ambiente existente
//     if (count == 1 || !ft_strrchr(arg[1], (int)'='))
//     {
//         show_func(__func__, SUCCESS);
//         printf("Export sem argumentos válidos\n"); // Indicação apenas 
//para teste, 
//não aparece no shell
//         return envp;
//     }

//     // Aloca memória para o novo array de strings
//     char **new_env = (char **)malloc(sizeof(char *) * 
//(count + env_count(envp) + 1));

//     if (!new_env)
//     {
//         perror("Malloc failed");
//         exit(EXIT_FAILURE);
//     }

//     int i = 0;

//     // Copia as variáveis de ambiente existentes para o novo array
//     while (envp[i])
//     {
//         new_env[i] = ft_strdup(envp[i]);
//         i++;
//     }

//     // Adiciona as novas variáveis de ambiente ao novo array
//     int j = 1;
//     while (j < count)
//     {
//         new_env[i] = ft_strdup(arg[j]);
//         i++;
//         j++;
//     }

//     new_env[i] = NULL; // Define a última entrada como NULL para 
//indicar o fim do array

//     show_func(__func__, SUCCESS);
//     return new_env;
// }
// NOVA VERSAO PARA IMPLEMENTAR ESTRUTURA, COM INDEX
/// @brief          add new environment variable to env
/// @param arg      new env variable to add 
/// @param envp     environment variables lis 
/// @return         the new env variables
/// STILL TESTING 
char	**export_cmd(t_script *s)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 1;
	show_func(__func__, MY_START);
	// Se não houver argumentos ou o argumento não contiver '=', 
	//retorna o ambiente existente
	if (s->commands->argc == 1 || !ft_strrchr(s->commands->argv[1], (int) '='))
	{
		show_func(__func__, SUCCESS);
		return (s->envp);
	}
	// Aloca memória para o novo array de strings
	new_env = (char **)malloc(sizeof(char *) * 
			(s->commands->argc + env_count(s->envp) + 1));
	if (!new_env)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
	}
	// Copia as variáveis de ambiente existentes para o novo array
	while (s->envp[i])
	{
		new_env[i] = ft_strdup(s->envp[i]);
		i++;
	}
	// Adiciona as novas variáveis de ambiente ao novo array
	while (j < s->commands->argc)
	{
		new_env[i] = ft_strdup(s->commands->argv[j]);
		i++;
		j++;
	}
	new_env[i] = NULL; // Define a última entrada como 
	//						NULL para indicar o fim do array
	show_func(__func__, SUCCESS);
	return (new_env);
}
