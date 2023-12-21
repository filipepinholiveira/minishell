/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:09:01 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/14 19:48:09 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin exit command
/// @param args		Builtin command arguments
/// @return			exit status or ERROR
int	exit_shell(t_script *s)
{
	show_func(__func__, MY_START);
	//int	count;

	//count = arg_count(args);
	if (s->commands->argc == 1)
		exit (0);
	if (s->commands->argc > 2)
	{
		if (ft_is_str_digit(s->commands->argv[1]) == 1)
		{
			printf("exit\nbash: exit: %s numeric argument required\n", s->commands->argv[1]);
			show_func(__func__, SUCCESS);
			exit (2);
		}
		else
		{
			printf("exit\nbash: exit: too many arguments\n");
			return (1);
		}
	}
	show_func(__func__, SUCCESS);
	exit (ft_atoi(s->commands->argv[1]));
}


// int	exit_shell(char **args)
// {
// 	show_func(__func__, MY_START);
// 	int	count;

// 	count = arg_count(args);
// 	if (count == 1)
// 		exit (0);
// 	if (count > 2)
// 	{
// 		if (ft_is_str_digit(args[1]) == 1)
// 		{
// 			printf("exit\nbash: exit: %s numeric argument required\n", args[1]);
// 			show_func(__func__, SUCCESS);
// 			exit (2);
// 		}
// 		else
// 		{
// 			printf("exit\nbash: exit: too many arguments\n");
// 			return (1);
// 		}
// 	}
// 	show_func(__func__, SUCCESS);
// 	exit (ft_atoi(args[1]));
// }
