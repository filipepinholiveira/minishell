/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/02 15:28:10 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin env command
/// @param args		Builtin command arguments
/// @param envp		Environment variables
/// @return			SUCCESS or ERROR
int	env_print(t_script *s)
{
	int	count;

	show_func(__func__, MY_START);
	count = 0;
	while (s->envp[count] != NULL)
	{
		write(STDOUT_FILENO, s->envp[count], ft_strlen(s->envp[count]));
		write(STDOUT_FILENO, "\n", 1);
		count++;
	}
	show_func(__func__, SUCCESS);
	return (count);
}
