/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   80ms_bi_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/30 17:25:00 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	bi_exec(t_script *s, int n, const void *func)
{
	int	(*f)(t_script*, int);

	f = func;
	return (f(s, n));
}

int	bi_child(t_script *s, int n, const void *func)
{
	int				(*f)(t_script*, int);

	f = func;
	if (s->commands[n].out.name)
		redir_out_go(s, n);
	if (s->commands[n].in.name)
		redir_in_go(s, n);
	return (f(s, n));
}

int	bi_pipe(t_script *s, int n, const void *func)
{
	show_func(__func__, MY_START, NULL);
	pid_t	pid;

	if (s->commands[0].in.flag == -1)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, sig_handler_fork);
	signal(SIGINT, sig_handler_fork);
	pid = fork();
	if (pid == -1)
		return (return_error("fork", errno, 0));
	if (pid == 0)
	{
		show_func(__func__, SHOW_MSG, "CHILD START");
		g_exit_status = bi_child(s, n, func);
		exit(g_exit_status);
	}
	else
	{
		wait(&g_exit_status);
		show_func(__func__, SHOW_MSG, "CHILD END");
		if (WIFEXITED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
		bi_env_upd(s, n);
	}
	show_func(__func__, SUCCESS, "CHILD Builin executed");
	return (0);
}

/// @brief 		Selects and Executes built in functions
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
int	bi_go(t_script *s, int n)
{
	show_func(__func__, MY_START, "NOVA VERSAO");
	const t_bi_cmd	bi_cmd[9] = {
	{"echo", bi_echo, s, n}, {"cd", bi_cd, s, n}, {"pwd", bi_pwd, s, n},
	{"export", bi_export, s, n}, {"unset", bi_unset, s, n},
	{"env", bi_env, s, n}, {"exit", bi_exit, s, n}, {NULL, NULL, NULL, 0}};
	int				i;

	i = -1;
	while (bi_cmd[++i].bi_cmd)
	{
		signal(SIGINT, sig_handler_fork);
		if (!ft_strncmp(bi_cmd[i].bi_cmd, s->commands[n].argv[0],
				ft_strlen(bi_cmd[i].bi_cmd)))
		{
			if (i == 0 || i == 2 || i == 5)
				return (bi_pipe(s, n, (char *)bi_cmd[i].bi_func));
			else
				return (bi_exec(s, n, (char *)bi_cmd[i].bi_func));
		}
	}
	show_func(__func__, ERROR, "Builtin NOT found");
	return (-1);
}

