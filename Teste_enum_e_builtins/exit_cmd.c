/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:09:01 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/06 16:42:12 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../SOURCES/minishell.h"


int	ft_is_str_digit(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
		{
			return (1);
		}
		i++;
	}
	return (0);
}



int arg_count_again(char **cmd)
{
    int count = 0;
    while (cmd[count])
        count++;
    return (count);
}




int	exit_shell(char **args)
{	
	int count = arg_count_again(args);
	//free_all(arg)
	if (count == 1)
		exit (0);
	if (count > 2)
	{
		if (ft_is_str_digit(args[1]) == 1)
		{
			printf("exit\nbash: exit: %s numeric argument required\n", args[1]);
			exit (2);
		}
		else
		{
			printf("exit\nbash: exit: too many arguments\n");
			return (1);
		}
	}
	exit (ft_atoi(args[1]));
}