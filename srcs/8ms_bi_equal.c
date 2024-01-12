/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/15 11:57:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// /// @brief 			Export TEMPORARY environment variables
// /// @param s 		Script structure with commans and args
// /// @param n 		Index of command to be executed
// /// @return 		SUCCESS or ERROR
// int		bi_equal(t_script *s, int n)
// {
// 	show_func(__func__, MY_START, NULL);
// 	int		i;
// 	char	*var_tp;
// 	char 	*var_tt;

// 	if (!s->envp || !s->commands[n].argv[0] || !s->commands[n].argv[0][0])
// 	{
// 		show_func(__func__, ERROR, "EXPORT args is empty");
// 		return (ERROR);
// 	}
// 	i = 0;
// 	while (s->commands[n].argv[i])
// 	{
// 		printf("%s&s->envp = %p%s\n", SBHPPL, s->envp, SRST);


// 		var_tp = env_var_getter(s->commands[n].argv[i], s->envp);
// 		var_tt = env_var_getter(s->commands[n].argv[i], s->envt);

// 		if (var_tp)
// 		{
// 			if (s->commands[n].argv[i + 2])
// 				env_var_setter(s->commands[n].argv[i + 2],
// 					s->commands[n].argv[i], &s->envp);
// 			else
// 				env_var_setter("", s->commands[n].argv[i], &s->envp);
// 		}
// 		else
// 		{
// 			if (s->commands[n].argv[i + 2])
// 				env_var_setter(s->commands[n].argv[i + 2],
// 					s->commands[n].argv[i], &s->envt);
// 			else
// 				if (var_tt)
// 					env_var_setter("", s->commands[n].argv[i], &s->envt);
// 		}
// 		i += 3;
// 	}
// 	show_func(__func__, SUCCESS, NULL);
// 	return (SUCCESS);
// }

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

	// if (!s->envp || !s->commands[n].argv[0] || !s->commands[n].argv[0][0])
	// {
	// 	show_func(__func__, ERROR, "EXPORT args is empty"); 
	// 	return (ERROR);
	// }
	i = 0;
	while (s->commands[n].argv[i])
	{
		printf("%s&s->envp = %p%s\n", SBHPPL, s->envp, SRST);
		printf("%ss->commands[n].argv[i]: %s\n", SBHPPL, s->commands[n].argv[i]);

		var_tp = env_var_getter(s->commands[n].argv[i], s->envp);
		var_tt = env_var_getter(s->commands[n].argv[i], s->envt);

		printf("valor de var_tp apos env_var_getter: %s\n", var_tp); // tem que retornar null se nao existir no envp mas nao esta a acontecer
		printf("valor de var_tt apos env_var_getter: %s\n", var_tt);

		if (var_tp && (ft_strncmp(var_tp, "", 1) != 0))
		{
			printf("entra no var_tp\n");
			if (ft_strchr(s->commands[n].argv[i], '='))
				env_var_setter(ft_strchr(s->commands[n].argv[i], '=') + 1,
					ft_substr(s->commands[n].argv[i], 0,
						ft_strlen(s->commands[n].argv[i])
						- ft_strlen(ft_strchr(s->commands[n].argv[i], '='))),
					&s->envp);
			else
				env_var_setter("", s->commands[n].argv[i], &s->envp);
			printf("sai do var_tp\n");
		}
		else
		{		
				if (var_tt)
				{
					printf("entra no var_tt\n");
					if (ft_strchr(s->commands[n].argv[i], '='))
						env_var_setter(ft_strchr(s->commands[n].argv[i], '=') + 1,
							ft_substr(s->commands[n].argv[i], 0,
								ft_strlen(s->commands[n].argv[i])
								- ft_strlen(ft_strchr(s->commands[n].argv[i], '='))),
					&s->envt);
				}
				else
					env_var_setter("", s->commands[n].argv[i], &s->envp);
		}
		i++;
	}
	free(var_tp);
	free(var_tt);
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
