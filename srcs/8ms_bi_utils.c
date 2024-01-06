/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:09:01 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/02 15:35:56 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief              count the number or env variables
/// @param envp         current environment variables
/// @return             number or varibles
int	env_count(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
	{
		count++;
	}
	return (count);
}

int	arg_count(char **args)
{
	int	count;

	show_func(__func__, MY_START, NULL);
	count = 0;
	while (args[count])
		count++;
	show_func(__func__, SUCCESS, NULL);
	return (count);
}

int	ft_is_str_digit(char *str)
{
	int	i;

	show_func(__func__, MY_START, NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
		{
			show_func(__func__, ERROR, NULL);
			return (1);
		}
		i++;
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

char	*get_location(char *command)
{
	char		*path;
	char		*path_copy;
	char		*path_token;
	char		*file_path;
	int			command_length;
	int			directory_length;
	struct stat	buffer;

	show_func(__func__, MY_START, NULL);
	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				show_func(__func__, SUCCESS, NULL);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		show_func(__func__, SUCCESS, NULL);
		return (NULL);
	}
	show_func(__func__, SUCCESS, NULL);
	return (NULL);
}
