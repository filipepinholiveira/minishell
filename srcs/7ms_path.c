/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:07:09 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/08 18:42:32 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_path_index(char **envp)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			show_func(__func__, SUCCESS,
				ft_strjoin("PATH index = ", ft_itoa(i)));
			return (i);
		}
		i++;
	}
	show_func(__func__, ERROR, NULL);
	return (-1);
}

char	**split_path(char **envp)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	char	**path;

	i = get_path_index(envp);
	if (i == -1)
		return (NULL);
	path = ft_split(envp[i] + 5, ':');

	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		show_func(__func__, MY_START, path[i]);
	}
	show_func(__func__, SUCCESS, NULL);
	return (path);
}
