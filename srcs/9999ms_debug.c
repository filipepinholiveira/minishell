/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9999ms_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:02 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/11 21:57:16 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "../include/minishell.h"

void	show_func_msg(const char *msg)
{
	if (MY_DEBUG)
	{
		if (!msg)
			write(2, "\n", 2);
		else
		{
			write(STDOUT_FILENO, "-> ", 3);
			write(STDOUT_FILENO, msg, ft_strlen(msg));
			//write(2, "\n", 1);
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
	const t_debug_msg	debug_msg[12] = {
	{" INFO", SHOW_MSG, 5, "(ii) ", SBHPPL},
	{" START", MY_START, 6, "\n(>) ", SHBLU},
	{" ERROR", ERROR, 6, "(xx) ", SHRED},
	{" SUCCESS", SUCCESS, 8, "(xx) ", SHGRN},
	{" MALLOC_ERROR", MALLOC_ERROR, 13, "(xx) ", SBHRED},
	{" MALLOC_NOT_ALLOCATED", MALLOC_NOT_ALLOCATED, 22, "(xx) ", SBHCYN},
	{" FILE_ERROR", FILE_ERROR, 11, "(xx) ", SBHRED},
	{" CHILD_EXIT", CHILD_EXIT, 11, "(xx) ", SBHYLW},
	{" EXIT_FAILURE", EXIT_FAILURE, 14, "(xx) ", SBHRED},
	{" FILE_NOT_FOUND", FILE_NOT_FOUND, 16, "(xx) ", SBHRED},
	{" FILE_NOT_DELETED", FILE_NOT_DELETED, 17, "(xx) ", SBHRED},
	{NULL, 0, 0, NULL, NULL}};

	if (MY_DEBUG)
	{
		i = -1;
		while (debug_msg[++i].status != status && debug_msg[i].msg)
		{
			if (debug_msg[i].status == status)
				break ;
		}
		if (MY_DEBUG_COLOR)
		{
			printf("%s%s%s%s%s%s%s", SBHWHT, debug_msg[i].msg_header, SBWHT, func_name,
				debug_msg[i].color, debug_msg[i].msg, SRST);
			if (msg)
				printf("%s-> %s%s\n", SBHCYN, msg, SRST);
			else
				printf("%s\n", SRST);
		}
		else
		{
			write(STDOUT_FILENO, debug_msg[i].msg_header, 5);
			write(STDOUT_FILENO, func_name, ft_strlen(func_name));
			write(STDOUT_FILENO, debug_msg[i].msg, debug_msg[i].len);
			show_func_msg(msg);
		}
	}
	return (status);
}
