/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:13:01 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/21 21:58:54 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	clear(void)
{
	printf("\033[2J");
	printf("\033[%d;%dH", 0, 0);
}

/// @brief		Post a welcome message with pre and pos clear screen
/// @return		void
void	init_shell(void)
{
	char	*username;

	username = getenv("USER");
	clear();
	printf("\nUSER is: @%s", username);
	printf("\n");
	sleep(1);
	clear();
}

/// @brief		Read a string, and add it to the history.
/// @param str	Pointer to the line to be read
/// @return		Pointer to the line read
int	get_input(char *str)
{
	char	*buf;

	buf = readline("\n>>> ");
	if (ft_strlen(buf) != 0)
	{
		add_history(buf);
		str = ft_strdup(buf);
		if (buf)
		{
			free(buf);
			buf = (char *) NULL;
		}
		return (SUCCESS);
	}
	else
		return (ERROR);
}

/// @brief			Print the current directory
void	print_dir_path(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
	if (cwd)
	{
		free(cwd);
		cwd = (char *) NULL;
	}
}

/// @brief 				Read a string, and return a pointer to it and add it to the history.
/// @param line_read	Pointer to the line to be read
/// @return				Pointer to the line read
char *rl_gets(void *line_read)
{
	/* If the buffer has already been allocated, return the memory to the free pool. */
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}

	/* Get a line from the user. */
	line_read = readline("Input your line:");

	/* If the line has any text in it, save it on the history. */

	if (line_read && *(char *)line_read)
		add_history(line_read);

	return (line_read);
}