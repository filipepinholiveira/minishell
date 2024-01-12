/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/11 18:31:48 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/// @brief 			Export TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int		bi_equal(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	char	*var_tp;
	char 	*var_tt;

	if (!s->envp || !s->commands[n].argv[1] || !s->commands[n].argv[1][0])
	{
		show_func(__func__, ERROR, "EXPORT args is empty");
		return (ERROR);
	}
	i = 0;
	while (s->commands[n].argv[i] && s->commands[n].argv[i + 1][0] == '=')
	{
		printf("%s&s->envp = %p%s\n", SBHPPL, s->envp, SRST);


		var_tp = env_var_getter(s->commands[n].argv[i], s->envp);
		var_tt = env_var_getter(s->commands[n].argv[i], s->envt);

		if (var_tp)
		{
			if (s->commands[n].argv[i + 2])
				env_var_setter(s->commands[n].argv[i + 2],
					s->commands[n].argv[i], &s->envp);
			else
				env_var_setter("", s->commands[n].argv[i], &s->envp);
		}
		else
		{
			if (s->commands[n].argv[i + 2])
				env_var_setter(s->commands[n].argv[i + 2],
					s->commands[n].argv[i], &s->envt);
			else
				if (var_tt)
					env_var_setter("", s->commands[n].argv[i], &s->envt);
		}
		i += 3;
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
