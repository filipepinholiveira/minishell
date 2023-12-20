/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/14 20:15:33 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*unset({"unset", "OLDPWD", NULL})
	char * p;
	fazer alteracao do OLDPWD e PWD com a funcao do antonio
	1o: OLDPWD = PWD;
	20: o PWD = getcwd(p, cd)
*/

int	unset(char *args[])
{
	show_func(__func__, MY_START);
	int	count;
	int	i;

	count = arg_count(args);
	i = 0;
	if (count == 1)
	{
		printf("Minishell: unset: not enough arguments\n");
		show_func(__func__, ERROR);
		return (ERROR);
	}
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "OLDPWD", 7) == 0)
		{
			printf("Minishell: unset: OLDPWD: cannot unset: readonly variable\n");
			show_func(__func__, ERROR);
			return (ERROR);
		}
		i++;
	}
	show_func(__func__, SUCCESS);
	return (SUCCESS);
}
