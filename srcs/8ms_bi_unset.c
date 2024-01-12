/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/12 23:53:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief Remove a variable from the environment
/// @param arg Arguments passed to unset command
/// @param envp Current environment variables
/// @return Updated environment variables
int	bi_unset(t_script *s, int n)
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
