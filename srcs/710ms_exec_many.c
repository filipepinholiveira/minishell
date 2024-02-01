/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   710ms_exec_many.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:00:28 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/02/01 17:03:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int first_child(t_script *s, int n)
{
	show_func(__func__, MY_START, s->cmds->argv[n]);
	exec_one(s, n);
		show_func(__func__, SUCCESS, NULL);
	return (0);
}

/// @brief 			Execute n commands in the script	
/// @param s		struct passed with commands
/// @param n		index of the command in s->cmds
/// @return			0 em caso de sucesso, encerra o programa em caso de falha.
int	exec_many(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int i;

	signal(SIGINT, sig_handler_fork);
	i = -1;
	while (++i < s->cmd_count)
	{
		prepare_fds(s, i);
		if (s->cmds[n].argc && get_cmd_type(s->cmds[n].argv[0]) != CMD_EXEC)
			g_exit_status = bi_go(s, n);
		else
			g_exit_status = exec_go(s, n);
		// if (i + 1 == 1)
		// {
		// 	// first command
		// 	execute_do_cmd_1(s, i);
		// }
		// else if (i + 1 == s->cmd_count)
		// {
		// 	// last command
		// 	execute_do_cmd_n(s, i);
		// }
		// else
		// {
		// 	// middle cmds
		// 	execute_do_cmd_i(s, i);
		// }
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
