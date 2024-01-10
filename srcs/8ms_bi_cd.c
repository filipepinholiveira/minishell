/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:46 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/10 22:25:01 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	change_dir(char *path, char ***envp)
{
	show_func(__func__, MY_START, path);
	int		ret;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH_LEN);
	ret = chdir(path);
	if (ret == -1)
		return (return_error(path, 1));
	env_var_setter(pwd, "OLDPWD", envp);
	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH_LEN);
	ret = env_var_setter(pwd, "PWD", envp);
	free(pwd);
	return (ret);
}

/// @brief 			Builtin cd command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
int	bi_cd(t_script *s, int n)
{
	show_func(__func__, MY_START,
		ft_strjoin("execute bi: ", s->commands[n].argv[0]));
	char	*home;
	int		status;

	if (!s->commands[n].argv[1])
	{
		home = env_var_getter("HOME", s->envp);
		if (home == NULL)
		{
			ft_putendl_fd("Minishell: cd: HOME not set", 2);
			free(home);
			return (1);
		}
		status = change_dir(home, &s->envp);
		free(home);
		return (status);
	}
	if (s->commands[n].argv[2])
	{
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
		show_func(__func__, ERROR, NULL);
		return (1);
	}
	if (s->commands[n].argv[1][0] == '\0')
	{
		status = change_dir(".", &s->envp);
		return (status);
	}
	status = change_dir(s->commands[n].argv[1], &s->envp);
	return (status);
}
