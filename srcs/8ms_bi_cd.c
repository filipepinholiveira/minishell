/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:46 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/14 19:09:47 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
para tratar, se localizaçao tiver espaço no nome conta como 2 args
e nao apenas 1
*/




/// @brief 			Builtin cd command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
int	cd_cmd(t_script *s)
{
	show_func(__func__, MY_START);
	char	*home;
	if (s->commands->argc > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		return (ERROR);
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
	show_func(__func__, SUCCESS);
	return (SUCCESS);
}

// ANTIGA SEM ARGUMENTO T_SCRIPT

// int	cd_cmd(char **args)
// {
// 	show_func(__func__, MY_START);
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
// 	show_func(__func__, SUCCESS);
// 	return (SUCCESS);
// }
