/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/15 11:50:46 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Export PERMANENT environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_export(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	if (!s->envp || !s->commands[n].argv[1] || !s->commands[n].argv[1][0])
		return (ERROR);
	i = 1;
	while (s->commands[n].argv[i])
	{
		if (var_name_check(s->commands[n].argv[i]))
			export_error(s->commands[n].argv[i], 1);
		else
		{
			if (ft_strchr(s->commands[n].argv[i], '='))
			{
				env_var_setter(ft_strchr(s->commands[n].argv[i], '=') + 1,
					ft_substr(s->commands[n].argv[i], 0,
						ft_strlen(s->commands[n].argv[i])
						- ft_strlen(ft_strchr(s->commands[n].argv[i], '='))),
					&s->envp);
			}
			else
				env_var_setter("", s->commands[n].argv[i], &s->envp);
		}
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
