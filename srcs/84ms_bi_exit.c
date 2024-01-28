/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:09:01 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/27 11:24:18 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin exit command
/// @param args		Builtin command arguments
/// @return			exit status or ERROR
int	bi_exit(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	env_var_setter("minishell","_", &s->envp);
	if (s->commands[n].argc == 1)
		exit (0);
	if (s->commands[n].argc > 2)
	{
		printf("exit\nbash: exit: too many arguments\n");
			return (1);
	}
	if (ft_is_str_digit(s->commands[n].argv[1]) == 1)
	{
		printf("Minishell: exit: '%s' numeric argument required\n",
			s->commands[n].argv[1]);
		show_func(__func__, SUCCESS, NULL);
		exit (2);
	}
	show_func(__func__, SUCCESS, NULL);
	exit (ft_atoi(s->commands[n].argv[1]));
}
