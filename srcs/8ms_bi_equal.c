/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/25 12:07:54 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	bi_equal_upd(t_script *s, int n, int i)
{
	env_var_setter(ft_strchr(s->commands[n].argv[i], '=') + 1,
		ft_substr(s->commands[n].argv[i], 0,
			ft_strlen(s->commands[n].argv[i])
			- ft_strlen(ft_strchr(s->commands[n].argv[i], '='))),
		&s->envp);
}
static void	bi_equal_new(t_script *s, int n, int i)
{
	env_var_setter(ft_strchr(s->commands[n].argv[i], '=') + 1,
		ft_substr(s->commands[n].argv[i], 0,
			ft_strlen(s->commands[n].argv[i])
			- ft_strlen(ft_strchr(s->commands[n].argv[i], '='))),
		&s->envt);
}


/// @brief 			Export TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_equal(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	int		index_tp;

	env_var_setter("","_", &s->envp);
	if (!s->envp || !s->commands[n].argv[0])
		return (ERROR);
	i = -1;
	while (s->commands[n].argv[++i])
	{
		if (var_name_check(s->commands[n].argv[i]) == SUCCESS)
		{
			index_tp = env_var_index_getter(ft_substr(s->commands[n].argv[i], 0,
						ft_strlen(s->commands[n].argv[i])
						- ft_strlen(ft_strchr(s->commands[n].argv[i], '='))),
					s->envp);
			if (index_tp != -1)
				bi_equal_upd(s, n, i);
			else
				bi_equal_new(s, n, i);
		}
		else
			export_error(s->commands[n].argv[i], 1);
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
