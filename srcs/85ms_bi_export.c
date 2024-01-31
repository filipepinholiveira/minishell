/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   85ms_bi_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/31 13:00:04 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief		Test validity of shell variables
/// @param var	Variable name to be tested
/// @return		SUCCESS or ERROR
int	var_name_check(char *var)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	i = 0;
	show_func(__func__, SHOW_MSG, var);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			show_func(__func__, ERROR, NULL);
			return (ERROR);
		}
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

static void	bi_export_upd_var(t_script *s, int n, int i)
{
	show_func(__func__, MY_START, NULL);
	char	*val;
	char	*var;

	var = ft_substr(s->cmds[n].argv[i], 0,
			ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	show_func(__func__, SHOW_MSG, var);
	val = ft_strchr(s->cmds[n].argv[i], '=') + 1;
	show_func(__func__, SHOW_MSG, val);

	env_var_setter(val, var, &s->envp);
	if (env_var_index_getter(var, s->envt) != -1)
		bi_unset_envt(s, n);
	show_func(__func__, SUCCESS, NULL);
}

static void	bi_export_new_var(t_script *s, int n, int i)
{
	show_func(__func__, MY_START, NULL);
	char	*val;
	char	*var;

	var = s->cmds[n].argv[i];
	show_func(__func__, SHOW_MSG, var);
	if (env_var_index_getter(var, s->envp) >= 0)
		return ;
	val = env_var_getter(var, s->envt);
	show_func(__func__, SHOW_MSG, val);
	if (val)
	{
		env_var_setter(val, var, &s->envp);
		bi_unset_envt(s, n);
	}
	show_func(__func__, SUCCESS, NULL);
}

/// @brief 			Export PERMANENT environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_export(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int		i;

	if (!s->envp || !s->cmds[n].argv[1] || !s->cmds[n].argv[1][0])
		return (ERROR);
	i = 1;
	while (s->cmds[n].argv[i])
	{
		if (var_name_check(s->cmds[n].argv[i]) == SUCCESS)
		{
			if (ft_strchr(s->cmds[n].argv[i], '='))
				bi_export_upd_var(s, n, i);
			else
				bi_export_new_var(s, n, i);
		}
		else
			export_error(s->cmds[n].argv[i], 1);
		i++;
	}
	env_var_setter(s->cmds[n].argv[--i],"_", &s->envp);
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
