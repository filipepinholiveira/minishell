/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:09:01 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/10 12:16:24 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin exit command
/// @param args		Builtin command arguments
/// @return			exit status or ERROR
int	bi_exit(t_script *s)
{
	show_func(__func__, MY_START, NULL);
	if (s->commands->argc == 1)
		exit (0);
	if (s->commands->argc > 2)
	{
		if (ft_is_str_digit(s->commands->argv[1]) == 1)
		{
			printf("exit\nbash: exit: %s numeric argument required\n",
				s->commands->argv[1]);
			show_func(__func__, SUCCESS, NULL);
			exit (2);
		}
		else
		{
			printf("exit\nbash: exit: too many arguments\n");
			return (1);
		}
	}
	show_func(__func__, SUCCESS, NULL);
	exit (ft_atoi(s->commands->argv[1]));
}
