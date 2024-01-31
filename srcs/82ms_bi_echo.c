/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   82ms_bi_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:43:00 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/31 11:09:27 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	bi_echo_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/// @brief 			Builtin echo command
/// @param command	Builtin command arguments
/// @return			SUCCESS if success, ERROR if error
//int	bi_echo(t_command commands)
int	bi_echo(t_script *s, int n)
{
	show_func(__func__, MY_START, ft_strjoin("execute bi: ", s->commands[n].argv[0]));
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	// if (!s->commands[n].argv[i])
	// 	env_var_setter("echo","_", &s->envp);
	// else
	// {
	if (s->commands[n].argv[i][0] == '-')
	{
		flag = bi_echo_flag(s->commands[n].argv[i]);
		if (flag)
			i++;
	}
	while (s->commands[n].argv[i])
	{
		ft_putstr_fd(s->commands[n].argv[i], STDOUT_FILENO);
		i++;
		if (s->commands[n].argv[i])
			write (STDOUT_FILENO, " ", 1);
	}
	// }
	if (!flag)
		write (STDOUT_FILENO, "\n", 1);
	// if (s->commands[n].argc > 1 && !flag)
	// 	env_var_setter(s->commands[n].argv[s->commands[n].argc - 1],"_", &s->envp);
	// else if (s->commands[n].argc == 2 && flag)
	// 	env_var_setter("","_", &s->envp);
	//free_commands(s->commands, n);
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 			Builtin echo command env var '_' update (last cmd)
/// @param s		Parsed script with command(s) to execute
/// @param n		Index of cmd to executes
/// @return			SUCCESS if success, ERROR if error
int bi_env_upd(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	if (!s->commands[n].argv[1])
		env_var_setter(s->commands[n].argv[0],"_", &s->envp);
	if (s->commands[n].argc > 1 && !bi_echo_flag(s->commands[n].argv[1]))
		env_var_setter(s->commands[n].argv[s->commands[n].argc - 1],"_", &s->envp);
	else if (s->commands[n].argc == 2 && bi_echo_flag(s->commands[n].argv[1]))
		env_var_setter("","_", &s->envp);
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
