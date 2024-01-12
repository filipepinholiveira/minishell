/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/12 20:55:43 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief Remove a variable from the environment
/// @param arg Arguments passed to unset command
/// @param envp Current environment variables
/// @return Updated environment variables
int bi_unset(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int i;
	int j;
	char *old_env;
	char *filter;

	if (!s->envp || !s->commands[n].argv[1] || !s->commands[n].argv[1][0])
	{
		show_func(__func__, ERROR, "UNSET args is empty");
		return (ERROR);
	}
	i = 1;
	while (s->commands[n].argv[i])
	{
		//if (ft_strchr(s->commands[n].argv[i], '='))
			filter = ft_substr(
					s->commands[n].argv[i], 0,
					ft_strlen(s->commands[n].argv[i])
					- ft_strlen(ft_strchr(s->commands[n].argv[i], '=')));
		//else
		//	filter = ft_strdup(s->commands[n].argv[i]);
		show_func(__func__, SHOW_MSG, filter);
		j = env_var_index_getter(filter, s->envp);
		if (j != -1)
		{
			while (s->envp[j])
			{
				old_env = s->envp[j];
				s->envp[j] = ft_strdup(s->envp[j + 1]);
				free(old_env);
				j++;
			}
		}
		free(filter);
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
// abc=123N
// 01234567
// strchr = str[3]
// strlen tudo = 7
// strlen strchr 4
// 7 - 4 = 3
// ft_strlcpy(str, 0, strlen tudo - strlen strchr)


//char	**bi_unset(t_script *s, int n)
// {
// 	int		i;
// 	int		j;
// 	char	**new_env;
// 	int		env_count;

// 	show_func(__func__, MY_START, NULL);
// 	i = 0;
// 	j = 0;
// 	env_count = 0;
// 	// Count the number of environment variables
// 	while (s->envp && s->envp[env_count])
// 		env_count++;
// 	if (s->commands->argv[1] == NULL)
// 	{
// 		printf("Unset sem argumentos válidos\n");
// 		return (s->envp);
// 	}
// 	// Allocate memory for the new environment array
// 	new_env = (char **)malloc(sizeof(char *) * (env_count + 1));
// 	if (!new_env)
// 		return (NULL);
// 	// Copy the variables from the old environment to the new one,
// 	// excluding the one specified in the arguments
// 	while (i < env_count)
// 	{
// 		if (ft_strncmp(s->commands->argv[1], s->envp[i],
// 				ft_strlen(s->commands->argv[1])) != 0)
// 		{
// 			new_env[j] = ft_strdup(s->envp[i]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_env[j] = NULL;
// 	return (new_env);
// }


