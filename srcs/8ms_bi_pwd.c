/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/09 00:31:25 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Builtin pwd command
/// @param void		Builtin command arguments not required
/// @return			SUCCESS or ERROR
int	bi_pwd_print(char **envp)
{
	show_func(__func__, MY_START, ft_strjoin("execute bi: ", "pwd"));
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, MAX_PATH_LEN);
	if (!buf)
	{
		free(buf);
		buf = get_env_ms("PWD", envp);
		ft_putendl_fd(buf, 1);
	}
	else
		ft_putendl_fd(buf, 1);
	show_func(__func__, SUCCESS, buf);
	free(buf);
	return (0);
}

// {
// 	show_func(__func__, MY_START, ft_strjoin("execute bi: ", "pwd"));
// 	char	s[100];

// 	if (getcwd(s, sizeof(s)) == NULL)
// 	{
// 		perror("getcwd");
// 		show_func(__func__, ERROR, NULL);
// 		return (1);
// 	}
// 	write (STDOUT_FILENO, s, strlen(s));
// 	write (STDOUT_FILENO, "\n", 1);
// 	show_func(__func__, SUCCESS, NULL);
// 	return (0);
// }
