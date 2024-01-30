/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   83ms_bi_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/30 17:23:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin env command
/// @param args		Builtin command arguments
/// @param envp		Environment variables
/// @return			SUCCESS or ERROR
int	bi_env(t_script *s)
{
	int	count;

	show_func(__func__, MY_START, NULL);
	//env_var_setter("env","_", &s->envp);
	count = 0;
	while (s->envp[count] != NULL)
	{
		write(STDOUT_FILENO, s->envp[count], ft_strlen(s->envp[count]));
		write(STDOUT_FILENO, "\n", 1);
		count++;
	}
	free_commands(s->commands, 0);
	show_func(__func__, SUCCESS, NULL);
	return (count);
}
