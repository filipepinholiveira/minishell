/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9999ms_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:02 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/02 15:51:38 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int	show_func(const char *func_name, int status, char *msg)
{
	if (MY_DEBUG)
	{
		if (!msg)
			printf("msg is empty!\n");
		
		if (status == ERROR)
			printf ("%s(X)%s %s : ERROR%s\n", SYLW, SRED, func_name, SWHT);
		else if (status == SUCCESS)
			printf ("%s(X)%s %s : SUCCESS%s\n", SYLW, SGRN, func_name, SWHT);
		else if (status == MY_START)
			printf ("\n%s(>)%s %s : START%s\n", SYLW, SYLW, func_name, SWHT);
		else if (status == MALLOC_ERROR)
			printf ("%s(>)%s %s : MALLOC_ERROR%s\n", SYLW, SYLW, 
				func_name, SWHT);
		else if (status == FILE_ERROR)
			printf ("%s(X)%s %s : FILE_ERROR%s\n", SYLW, SRED, func_name, SWHT);
		else if (status == CHILD_EXIT)
			printf ("%s(X)%s %s : CHILD_EXIT%s\n", SYLW, SRED, func_name, SWHT);
		else if (status == EXIT_FAILURE)
			printf ("%s(X)%s %s : EXIT_FAILURE%s\n", SYLW, SRED, func_name, SWHT);
		
	}
	return (status);
}
