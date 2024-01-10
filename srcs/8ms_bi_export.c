/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/10 22:46:46 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// NOVA VERSAO PARA IMPLEMENTAR ESTRUTURA, COM INDEX
/// @brief          add new environment variable to env
/// @param arg      new env variable to add
/// @param envp     environment variables lis
/// @return         the new env variables
/// STILL TESTING
//int	bi_export(t_script *s, t_command cmd)
int	bi_export(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	char	*var_t1;
	char 	*var_t2;

	if (!s->envp || !s->commands[n].argv[1] || !s->commands[n].argv[1][0])
	{
		show_func(__func__, ERROR, "EXPORT args is empty");
		return (ERROR);
	}
	i = 1;
	while (s->commands[n].argv[i])
	{
		var_t2 = env_var_getter(s->commands[n].argv[i], s->envp);
		printf("%s EXPORT (11) vars argv[%d] = '%s'%s\n",
			SBRED, i, s->commands[n].argv[i], SRST);
		printf("%s EXPORT (12) vars var_t2[%d] = '%s'%s\n",
			SBRED, i, var_t2, SRST);
		if (s->commands[n].argv[i + 1])
		{
			printf("%s EXPORT (21) vars argv[%d] = '%s'%s\n",
				SBRED, i + 1, s->commands[n].argv[i + 1], SRST);
			env_var_setter((s->commands[n].argv[i + 1]),
				(s->commands[n].argv[i]), &s->envp);
		}
		else
		{
			printf("%s EXPORT (31) vars argv[%d] = '%s'%s\n",
				SBRED, i, s->commands[n].argv[i], SRST);
			var_t1 = env_var_getter(s->commands[n].argv[i], s->envt);
			if (var_t1)
			{
				printf("%s EXPORT (41) vars argv[%d] = '%s'%s\n",
					SBRED, i, s->commands[n].argv[i], SRST);
				env_var_setter(var_t1, s->commands[n].argv[i], &s->envp);
			}
			show_func(__func__, SUCCESS, var_t1);
			return (SUCCESS);
		}
		i += 2;
	}
	show_envp(s->envp);
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
