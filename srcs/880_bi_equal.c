/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   880_bi_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:14:30 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 20:17:44 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Update EXISTING TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_upd(t_script *s, int n, int i)
{
	// estava a dar leak de memoria no substr dentro da env_var_setter, nao dava free
	char *var = ft_substr(s->cmds[n].argv[i], 0,
			ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	env_var_setter(ft_strchr(s->cmds[n].argv[i], '=') + 1, var, &s->envp);
		free(var);
}

/// @brief 			Creates NEW TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_new(t_script *s, int n, int i)
{
	char	*var;
	char	*val;

	var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	val = ft_strdup(ft_strchr(s->cmds[n].argv[i], '=') + 1);
	env_var_setter(val, var, &s->envt);
	ft_free(var);
	ft_free(val);
}
int index_tp_getter(t_script *s, int n, int i)
{
	char	*var;
	int		var_index;

	var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));

	var_index = env_var_index_getter(var, s->envp);
	ft_free(var);
	return (var_index);
}

/// @brief 			Export TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_equal(t_script *s, int n)
{
	// show_func(__func__, MY_START, NULL);
	int		i;
	int		var_index;

	if (!s->envp || !s->cmds[n].argv[0])
		return (ERROR);
	env_var_setter("","_", &s->envp);
	i = -1;
	while (s->cmds[n].argv[++i])
	{
		if (var_name_check(s->cmds[n].argv[i]) == SUCCESS)
		{
			var_index = index_tp_getter(s, n, i);
			if (var_index != -1)
				bi_equal_upd(s, n, i);
			else
				bi_equal_new(s, n, i);
		}
		else
			export_error(s->cmds[n].argv[i], 1);
	}
	// show_array(s->envt, "bi_equal envt");
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

// int bi_equal_type(char **var, char **envp)
// {
// 	int		i;
// 	int		index_tp;

// 	if (!envp || !var[0])
// 		return (ERROR);
// 	i = -1;
// 	while (var[++i])
// 	{
// 		if (var_name_check(var[i]) == SUCCESS)
// 		{

// 		}
// 		else
// 			..._error(var[i], 1);
// 	}
// 	return (SUCCESS);
// }