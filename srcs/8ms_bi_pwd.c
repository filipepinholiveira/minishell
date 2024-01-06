/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/02 15:35:09 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin pwd command
/// @param void		Builtin command arguments not required
/// @return			SUCCESS or ERROR
int	pwd_print(void)
{
	char	s[100];

	show_func(__func__, MY_START, NULL);
	if (getcwd(s, sizeof(s)) == NULL)
	{
		perror("getcwd");
		show_func(__func__, ERROR, NULL);
		return (1);
	}
	write (STDOUT_FILENO, s, strlen(s));
	write (STDOUT_FILENO, "\n", 1);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
