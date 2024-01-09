/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:43:00 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/08 23:03:54 by antoda-s         ###   ########.fr       */
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
int	bi_echo_print(t_command commands)
{
	show_func(__func__, MY_START, ft_strjoin("execute bi: ", commands.argv[0]));
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!commands.argv[i])
		write(1, "\n", 1);
	else
	{
		if (commands.argv[i][0] == '-')
		{
			flag = bi_echo_flag(commands.argv[i]);
			if (flag)
				i++;
		}
		while (commands.argv[i])
		{
			ft_putstr_fd(commands.argv[i], 1);
			i++;
			if (commands.argv[i])
				write (1, " ", 1);
		}
		if (!flag)
			write (1, "\n", 1);
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}
