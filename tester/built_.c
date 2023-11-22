/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:38:51 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/21 23:40:27 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		Execute builtin command exit
/// @param args	Pointer to the command to be executed
/// @return		SUCCESS after completion
int	cd_command(char **args)
{
	char	*home;

	home = getenv("HOME");
	if (args[1] == NULL)
	{
		if (home == NULL)
		{
			perror("cd");
			return (ERROR);
		}

		if (chdir(home) != 0)
		{
			perror("cd");
			return (ERROR);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 		Execute builtin command hello
/// @param		void
/// @return		SUCCESS after completion
int	show_hello(void)
{
	char	*username;

	username = getenv("USER");
	ft_putstr_fd("\nHello ", 1);
	ft_putstr_fd(username, 1);
	ft_putstr_fd(".\nWhat do you wanna shell today?"
		"\nUse help to know more..\n", 1);
	return (SUCCESS);
}

/// @brief 		Execute builtin command help
/// @param		void
void	show_help(void)
{
	ft_putstr_fd("\n***Welcome to Minishell help***"
		"\nCopyright @ fpinho + antoda"
		"\nAre you sure you know how to use a shell?"
		"\nList of built-in commands:"
		"\n>cd"
		"\n>ls"
		"\n>exit"
		"\n>all other general commands available from UNIX shell"
		"\n>pipe & redirect handling"
		"\n>space trim & clean handling", 1);

	return (SUCCESS);
}

