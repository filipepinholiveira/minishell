/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   880_bi_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:14:30 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:31:15 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Export TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_equal(t_script *s, int n)
{
	// show_func(__func__, MY_START, NULL);
	int		i;
	//int		index_tp;

	if (!s->envp || !s->cmds[n].argv[0])
		return (ERROR);
	env_var_setter("","_", &s->envp);
	i = -1;
	while (s->cmds[n].argv[++i])
	{
		if (ft_strchr(s->cmds[n].argv[i], '+') != NULL)
			bi_equal_apend(s, n, i);
		else if (ft_strchr(s->cmds[n].argv[i], '+') == NULL)
			bi_equal_not_apend(s, n, i);
		else
			export_error(s->cmds[n].argv[i], 1);
	}
	show_array(s->envt, "bi_equal envt");
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