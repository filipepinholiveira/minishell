/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/09 22:30:03 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// NOVA VERSAO PARA IMPLEMENTAR ESTRUTURA, COM INDEX
/// @brief          add new environment variable to env
/// @param arg      new env variable to add
/// @param envp     environment variables lis
/// @return         the new env variables
/// STILL TESTING
int	bi_export(t_script *s, t_command cmd)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	if (!s->envp || !cmd.argv[1] || !cmd.argv[1][0])
	{
		show_func(__func__, SUCCESS, NULL);
		return (ERROR);
	}
	i = -1;
	while (cmd.argv[++i])
	{
		printf("%s EXPORT vars cmd.argv[%d] = %s%s\n", SBRED, i, cmd.argv[i], SRST);
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
// int	export_cmd(t_script *s)
// {
// 	show_func(__func__, MY_START, NULL);
// 	int		i;
// 	int		j;
// 	char	**new_env;
// 	int		res;;

// 	i = 0;
// 	j = 1;
// 	// Se não houver argumentos ou o argumento não contiver '=',
// 	//retorna o ambiente existente
// 	if (s->commands->argc == 1 || !ft_strrchr(s->commands->argv[1], (int) '='))
// 	{
// 		show_func(__func__, SUCCESS, NULL);
// 		return (s->envp);
// 	}
// 	// Aloca memória para o novo array de strings
// 	new_env = (char **)malloc(sizeof(char *) *
// 			(s->commands->argc + env_count(s->envp) + 1));
// 	if (!new_env)
// 	{
// 		perror("Malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	// Copia as variáveis de ambiente existentes para o novo array
// 	while (s->envp[i])
// 	{
// 		new_env[i] = ft_strdup(s->envp[i]);
// 		i++;
// 	}
// 	// Adiciona as novas variáveis de ambiente ao novo array
// 	while (j < s->commands->argc)
// 	{
// 		new_env[i] = ft_strdup(s->commands->argv[j]);
// 		i++;
// 		j++;
// 	}
// 	new_env[i] = NULL; // Define a última entrada como
// 	//						NULL para indicar o fim do array
// 	show_func(__func__, SUCCESS, NULL);
// 	return (new_env);
// }
