/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:46 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/02 15:25:22 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin cd command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
int	cd_cmd(t_script *s)
{
	char	*home;
	char	*special_path;
	int		i;

	show_func(__func__, MY_START, NULL);
	i = 1;
	special_path = ft_strdup(s->commands->argv[i]);
	if (s->commands->argc > 2)
	{
		while (i < s->commands->argc && s->commands->argv[i + 1] != NULL)
		{
			special_path = ft_strjoin(special_path, " ");
			special_path = ft_strjoin(special_path, s->commands->argv[i + 1]);
			i++;
		}
		if (chdir(special_path) != 0)
		{
			printf("Minishell: cd: too many arguments\n");
			return (ERROR);
		}
		else
		{
			show_func(__func__, SUCCESS, NULL);
			return (SUCCESS);
		}
	}
	if (s->commands->argv[1] == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			perror("Minishell: cd");
			return (ERROR);
		}
		if (chdir(home) != 0)
		{
			perror("Minishell: cd");
			return (ERROR);
		}
	}
	else
	{
		if (chdir(s->commands->argv[1]) != 0)
		{
			perror("Minishell: cd");
			return (ERROR);
		}
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

// ANTIGA SEM ARGUMENTO T_SCRIPT

// int	cd_cmd(char **args)
// {
// 	show_func(__func__, MY_START, NULL);
// 	int		count;
// 	char	*home;

// 	count = arg_count(args);
// 	if (count > 2)
// 	{
// 		printf("Minishell: cd: too many arguments\n");
// 		return (ERROR);
// 	}
// 	if (args[1] == NULL)
// 	{
// 		home = getenv("HOME");
// 		if (home == NULL)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 		if (chdir(home) != 0)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 	}
// 	else
// 	{
// 		if (chdir(args[1]) != 0)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 	}
// 	show_func(__func__, SUCCESS, NULL);
// 	return (SUCCESS);
// }
