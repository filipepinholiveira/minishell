/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   814ms_bi_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:09:01 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/02/03 13:04:49 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	exit_error_args(const char *msg, int system)
{
	show_func(__func__, MY_START, NULL);

	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(msg, 2);
	errno = system;
	show_func(__func__, SUCCESS, NULL);
	return (system);
}

int	exit_error_notnum(const char *msg, int system)
{
	show_func(__func__, MY_START, NULL);

	ft_putstr_fd("Minishell: exit: '", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("':  numeric argument required\n", 2);
	errno = system;
	show_func(__func__, SUCCESS, NULL);
	return (system);
}

/// @brief 			Builtin exit command
/// @param args		Builtin command arguments
/// @return			exit status or ERROR
int	bi_exit(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);

	env_var_setter("minishell", "_", &s->envp);
	if (s->cmds[n].argc == 1)
		exit (0);
	if (s->cmds[n].argc > 2)
	{
		return (exit_error_args("too many arguments\n", 2));
	}
	if (ft_is_str_digit(s->cmds[n].argv[1]) == 1)
	{
		show_func(__func__, ERROR, NULL);
		exit_error_notnum(s->cmds[n].argv[1], 2);
		free_commands(s->cmds, s->cmd_count);
		free_envp(s->envp);
		exit (2);
	}
	show_func(__func__, SUCCESS, NULL);
	exit (ft_atoi(s->cmds[n].argv[1]));
}
