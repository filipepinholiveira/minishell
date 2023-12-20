/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:43:00 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/14 18:36:50 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int arg_count(char **cmd)
// {
// 		int count = 0;
// 		while (cmd[count])
// 				count++;
// 		return (count);
// }


/*
 echo;
 echo -n;
 echo filipe;
 echo -n filipe;
 echo filipe ...;
 echo -n filipe ...;

contar argumentos, até dois tratar direto; três se o 2º for -n tratar direto;
três ou mains (sem -n) criar loop para imprimir todos os argumentos

tratar expander
*/

/// @brief 		Builtin echo command
/// @param args	Builtin command arguments
/// @return		0 if success, 1 if error
int	echo_print(char **args)
{
	show_func(__func__, MY_START);
	int	count;
	int	i;

	count = arg_count(args);
	if (count == 1)
		printf("\n");
	else if ((count == 2) && (strcmp(args[1], "-n") == 0))
		return (0);
	else if ((count == 2) && (strcmp(args[1], "-n") != 0))
		printf("%s\n", args[1]);
	else if ((count >= 3) && (strcmp(args[1], "-n") == 0))
	{
		i = 2;
		while (i < count && args[i])
		{
			ft_putstr_fd(args[i], 1);
			i++;
			if (i != count)
				write (1, " ", 1);
		}
	}
	else if ((count >= 3) && (strcmp(args[1], "-n") != 0))
	{
		i = 1;
		while (i < count && args[i])
		{
			ft_putstr_fd(args[i], 1);
			write (1, " ", 1);
			i++;
		}
		write (1, "\n", 1);
	}
	show_func(__func__, SUCCESS);
	return (0);
}
