/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   80ms_bi_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/27 11:52:20 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		Selects and Executes built in functions
/// @param s 	Parsed script with command(s) to execute
/// @param n 	Index of the command to be executed
/// @return		0 if success, 1 if failure,...
int	bi_go(t_script *s, int n)
{
	show_func(__func__, MY_START, "NOVA VERSAO");
	const t_bi_cmd	bi_cmd[9] = {
	{"echo", bi_echo, s, n},
	{"cd", bi_cd, s, n},
	{"pwd", bi_pwd, s, n},
	{"export", bi_export, s, n},
	{"unset", bi_unset, s, n},
	{"env", bi_env, s, n},
	{"exit", bi_exit, s, n},
	{NULL, NULL, NULL, 0}};
	int				i;
	int				(*f)(t_script*, int);

	i = -1;

	while (bi_cmd[++i].bi_cmd)
	{

		signal(SIGINT, sig_handler_fork);
		if (!ft_strncmp(bi_cmd[i].bi_cmd, s->commands[n].argv[0], ft_strlen(bi_cmd[i].bi_cmd)))
		{
			if (s->commands[0].out.name)
				{
					printf("Reconhece p ficheiro de escrita e vai...  \n");
					if (s->commands[0].out.flag == 578)
					{
						printf("abrir e truncar\n");
						int file = open(s->commands[0].out.name, O_WRONLY | O_TRUNC);
						if (file == -1)
							return (ERROR);
						dup2(file, STDOUT_FILENO);
						close (file);
					}
					if (s->commands[0].out.flag == 1090)
					{
						printf("abrir e concatenar\n");
						int file = open(s->commands[0].out.name, O_WRONLY | O_APPEND);
						if (file == -1)
							return (ERROR);
						dup2(file, STDOUT_FILENO);
						close (file);
					}
				}
			if (s->commands[0].in.name)
				{
					printf("Reconhece p ficheiro de leitura\n");
					int file = open(s->commands[0].in.name, O_RDONLY);
					if (file == -1)
						return (ERROR);
					dup2(file, STDIN_FILENO);
					close (file);
				}
			f = bi_cmd[i].bi_func;
			return (f(bi_cmd[i].script, bi_cmd[i].n));
		}
	}
	show_func(__func__, ERROR, "Built In NOT found");
	return (-1);
}
