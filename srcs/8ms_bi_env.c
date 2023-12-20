/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/14 19:47:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin env command
/// @param args		Builtin command arguments
/// @param envp		Environment variables
/// @return			SUCCESS or ERROR
int	env_print(char **args, char **envp)
{
	show_func(__func__, MY_START);
	int	count;

	count = 0;
	(void)args;
	while (envp[count] != NULL)
	{
		printf("%s\n", envp[count]); // nao usar printf
		count++;
	}
	show_func(__func__, SUCCESS);
	return (count);
}