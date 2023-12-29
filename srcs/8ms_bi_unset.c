/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/29 13:43:26 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief Remove a variable from the environment
/// @param arg Arguments passed to unset command
/// @param envp Current environment variables
/// @return Updated environment variables
char	**unset_cmd(t_script *s)
{
	int		i;
	int		j;
	char	**new_env;
	int		env_count;

	show_func(__func__, MY_START);
	i = 0;
	j = 0;
	env_count = 0;
	// Count the number of environment variables
	while (s->envp && s->envp[env_count])
		env_count++;
	if (s->commands->argv[1] == NULL)
	{
		printf("Unset sem argumentos válidos\n");
		return (s->envp);
	}
	// Allocate memory for the new environment array
	new_env = (char **)malloc(sizeof(char *) * (env_count + 1));
	if (!new_env)
		return (NULL);
	// Copy the variables from the old environment to the new one,
	// excluding the one specified in the arguments
	while (i < env_count)
	{
		if (ft_strncmp(s->commands->argv[1], s->envp[i], 
				ft_strlen(s->commands->argv[1])) != 0)
		{
			new_env[j] = ft_strdup(s->envp[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}
