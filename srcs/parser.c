/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/29 00:16:20 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Checks if the number of arguments is valid
/// @param argc		Number of arguments
/// @return			SUCCESS if valid, ERROR if invalid
int	invalid_argc(int argc)
{
	show_func(__func__, MY_START);
	if (argc == 1)
	{
		printf("\t%s : Invalid number of arguments : %d\n", __func__, argc);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : Valid number of arguments:%d\n", __func__, argc);
	}
	return (show_func(__func__, SUCCESS));
}

/// @brief 			Checks if str has paired quotes and double quotes
/// @param str		String to parse
/// @param c		Character to check
/// @return
int	invalid_pair(char *str, char *c)
{
	int	i;
	int	k;

	show_func(__func__, MY_START);
	k = 0;
	if (!str || !c)
	{
		printf("\t%s : str or c == NULL\n", __func__);
		return (show_func(__func__, ERROR));
	}
	while (*c != '\0')
	{
		i = -1;
		while (str[++i] != '\0')
		{
			if (str[i] == *c)
				k++;
		}
		c++;
	}
	if (k % 2 != 0)
	{
		printf("\t%s : Invalid pairing : k(%c) = %d\n", __func__, *c, k);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : Valid quotes pairing\n", __func__);
		return (show_func(__func__, SUCCESS));
	}
}

/// @brief 				Checks if the quotes are valid
/// @param cmdline		Command line
/// @return				SUCCESS if valid, ERROR if invalid
int	invalid_quotes(char *line)
{
	show_func(__func__, MY_START);
	if (invalid_pair(line, "\"\'"))
		return (show_func(__func__, ERROR));
	return (show_func(__func__, SUCCESS));
}

/// @brief 			Checks if the argument is valid
/// @param argv		Argument
/// @return			SUCCESS if valid, ERROR if invalid
int	invalid_line(char *line)
{
	show_func(__func__, MY_START);
	if (line == NULL)
	{
		printf("\t%s : line  == NULL\n", __func__);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : line != NULL : %s\n", __func__, line);

		if (invalid_quotes(line))
			return (show_func(__func__, ERROR));
	}
	return (show_func(__func__, SUCCESS));
}
