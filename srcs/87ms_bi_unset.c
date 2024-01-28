/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/25 12:07:26 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Remove a variable from the PERMANENT environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int	bi_unset(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	int		j;
	char	*var;

	env_var_setter(s->commands[n].argv[s->commands[n].argc - 1],"_", &s->envp);
	if (!s->envp || !s->commands[n].argv[1])
		return (ERROR);
	i = 1;
	while (s->commands[n].argv[i])
	{
		if (!ft_strchr(s->commands[n].argv[i], '='))
		{
			j = env_var_index_getter(s->commands[n].argv[i], s->envp);
			while (j >= 0 && s->envp[j] && s->envp[j + 1])
			{
				var = s->envp[j];
				s->envp[j] = ft_strdup(s->envp[j + 1]);
				free(var);
				j++;
			}
			s->envp[j] = NULL;
		}
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 			Remove a variable from the TEMPORARY environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int	bi_unset_envt(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	int		j;
	char	*var;

	if (!s->envp || !s->commands[n].argv[1])
		return (ERROR);
	i = 1;
	while (s->commands[n].argv[i])
	{
		if (!ft_strchr(s->commands[n].argv[i], '='))
		{
			j = env_var_index_getter(s->commands[n].argv[i], s->envt);
			while (j >= 0 && s->envt[j] && s->envt[j + 1])
			{
				var = s->envp[j];
				s->envt[j] = ft_strdup(s->envt[j + 1]);
				free(var);
				j++;
			}
			s->envt[j] = NULL;
		}
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
