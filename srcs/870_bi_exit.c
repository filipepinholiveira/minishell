/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   870_bi_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:10:23 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 21:27:14 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Builtin 'exit' command argument checker
/// @param str		Builtin 'exit' argument string
/// @return			SUCSESS or ERROR
int	ft_is_str_digit(char *str)
{
	int	i;

	// show_func(__func__, MY_START, NULL);
	i = 0;
	while (str[i])
	{
		if ((str[i] < 48 || str[i] > 57) && str[0] != '-')
		{
			//show_func(__func__, ERROR, NULL);
			return (ERROR);
		}
		i++;
	}
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	exit_error_args(const char *msg, int system)
{
	// show_func(__func__, MY_START, NULL);

	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(msg, 2);
	errno = system;
	// show_func(__func__, SUCCESS, NULL);
	return (system);
}

// int	exit_error_notnum(const char *msg, int system)
// {
// 	// show_func(__func__, MY_START, NULL);

// 	ft_putstr_fd("Minishell: exit: ", 2);
// 	ft_putstr_fd(msg, 2);
// 	ft_putstr_fd(":  numeric argument required\n", 2);
// 	errno = system;
// 	//show_func(__func__, SUCCESS, NULL);
// 	return (system);
// }

void	exit_go(t_script *s, char *arg, char *msg, int sys)
{
	// show_func(__func__, MY_START, NULL);

	ft_putstr_fd("exit\n", 2);
	if (sys > 0 && (arg || msg))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		if (arg)
			ft_putstr_fd(arg, 2);
		if (msg)
			ft_putstr_fd(msg, 2);
	}
	errno = sys;
	free_commands(s->cmds, s->cmd_count);
	free_array(s->envp);
	// free_array_name(s->envp, "s->envp");
	free_array(s->envt);
	// free_array_name(s->envt, "s->envt");
	exit(sys);
	// show_func(__func__, SUCCESS, NULL);
}

/// @brief 			Builtin exit command limited to 9223372036854775807
/// @param args		Builtin command arguments
/// @return			exit status or ERROR
int	bi_exit(t_script *s, int n)
{
	// show_func(__func__, MY_START, NULL);
	char *trim;

	trim = NULL;
	env_var_setter("minishell", "_", &s->envp);
	if (s->cmds[n].argc == 1)
		exit_go(s, NULL, NULL, 0);
	else if (s->cmds[n].argc > 2)
	{
		// show_func(__func__, SUCCESS, ft_strdup(s->cmds[n].argv[2]));
		g_exit_status = exit_error_args("too many arguments\n", 1);
	}
	else if (s->cmds[n].argc == 2)
	{

		if (ft_is_str_digit(s->cmds[n].argv[1]) == 1)
			exit_go(s, s->cmds[n].argv[1], ": numeric argument required\n", 2);
		trim = ft_strtrim_leading(s->cmds[n].argv[1], "0");
		free (s->cmds[n].argv[1]);
		s->cmds[n].argv[1] = trim;
		if (ft_atoll(trim) > __LONG_LONG_MAX__ || ft_atoll(trim) < -9223372036854775808.0)
			exit_go(s, trim, ": numeric argument required\n", 2);
		else
			exit_go(s, NULL, NULL, ft_atoi(trim) % 256);
	}
	// show_func(__func__, SUCCESS, NULL);
	return (0);
}
