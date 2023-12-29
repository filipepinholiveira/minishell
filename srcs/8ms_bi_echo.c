/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:43:00 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/29 13:47:24 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		Builtin echo command
/// @param args	Builtin command arguments
/// @return		0 if success, 1 if error
int	echo_print(t_script *s)
{
	int	i;

	show_func(__func__, MY_START);
	if (s->commands->argc == 1)
		printf("\n");
	else if ((s->commands->argc == 2) && (strcmp(s->commands->argv[1], 
				"-n") == 0))
		return (0);
	else if ((s->commands->argc == 2) && (strcmp(s->commands->argv[1], 
				"-n") != 0))
		printf("%s\n", s->commands->argv[1]);
	else if ((s->commands->argc >= 3) && (strcmp(s->commands->argv[1], 
				"-n") == 0))
	{
		i = 2;
		while (i < s->commands->argc && s->commands->argv[i])
		{
			ft_putstr_fd(s->commands->argv[i], 1);
			i++;
			if (i != s->commands->argc)
				write (1, " ", 1);
		}
	}
	else if ((s->commands->argc >= 3) && (strcmp(s->commands->argv[1], 
				"-n") != 0))
	{
		i = 1;
		while (i < s->commands->argc && s->commands->argv[i])
		{
			ft_putstr_fd(s->commands->argv[i], 1);
			write (1, " ", 1);
			i++;
		}
		write (1, "\n", 1);
	}
	show_func(__func__, SUCCESS);
	return (0);
}
