/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9999ms_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:02 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/09 12:16:23 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "../include/minishell.h"

void	show_func_msg(const char *msg)
{
	if (MY_DEBUG)
	{
		if (!msg)
			write(2, "\n", 1);
		else
		{
			write(2, "-> ", 3);
			write(2, msg, ft_strlen(msg));
			write(2, "\n", 1);
		}
	}
}

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int	show_func(const char *func_name, int status, char *msg)
{
	int					i;
	const t_debug_msg	debug_msg[] = {
	{" START", MY_START, 6, "\n(>) "},
	{" ERROR", ERROR, 6, "\n(x) "},
	{" SUCCESS", SUCCESS, 8, "\n(x) "},
	{" MALLOC_ERROR", MALLOC_ERROR, 13, "\n(x) "},
	{" MALLOC_NOT_ALLOCATED", MALLOC_NOT_ALLOCATED, 22, "\n(x) "},
	{" FILE_ERROR", FILE_ERROR, 11, "\n(x) "},
	{" CHILD_EXIT", CHILD_EXIT, 11, "\n(x) "},
	{" EXIT_FAILURE", EXIT_FAILURE, 14, "\n(x) "},
	{" FILE_NOT_DELETED", FILE_NOT_DELETED, 17, "\n(x) "},
	{NULL, 0, 0, NULL}};

	if (MY_DEBUG)
	{
		i = -1;
		while (debug_msg[++i].status)
			if (debug_msg[i].status == status)
				break ;
		write(2, debug_msg[i].msg_header, 5);
		write(2, func_name, ft_strlen(func_name));
		write(2, debug_msg[i].msg, debug_msg[i].len);
		show_func_msg(msg);
	}
	return (status);
}

		// if (status == MY_START)
		// 	printf("\n%s(>)%s %s : START%s ", SWHT, SYLW, func_name, SWHT);
		// else if (status == ERROR)
		// 	printf("%s(X)%s %s : ERROR%s ", SWHT, SRED, func_name, SWHT);
		// else if (status == SUCCESS)
		// 	printf("%s(X)%s %s : SUCCESS%s  ", SWHT, SGRN, func_name, SWHT);
		// else if (status == MALLOC_ERROR)
		// 	printf("%s(x)%s %s : MALLOC_ERROR%s ", SWHT, SYLW,
		// 		func_name, SWHT);
		// else if (status == MALLOC_NOT_ALLOCATED)
		// 	printf("%s(x)%s %s : MALLOC_NOT_ALLOCATED%s ", SWHT, SYLW,
		// 		func_name, SWHT);
		// else if (status == FILE_ERROR)
		// 	printf("%s(X)%s %s : FILE_ERROR%s ", SWHT, SRED, func_name, SWHT);
		// else if (status == CHILD_EXIT)
		// 	printf("%s(X)%s %s : CHILD_EXIT%s ", SWHT, SRED, func_name, SWHT);
		// else if (status == EXIT_FAILURE)
		// 	printf("%s(X)%s %s : EXIT_FAILURE%s\n", SWHT, SRED,
		// 		func_name, SWHT);
