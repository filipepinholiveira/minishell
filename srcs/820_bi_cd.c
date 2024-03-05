/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   820_bi_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:44:19 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 21:52:33 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Changes the current directory and updates env var PWD OLDPWD
/// @param path 	New directory path
/// @param envp 	Environment variables
/// @return 		SUCCESS or ERROR
int	change_dir(char *path, char ***envp)
{
	// show_func(__func__, MY_START, ft_strdup(path));
	int		ret;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH_LEN);
	ret = chdir(path);
	if (ret == -1)
		return (return_error(path, 1, 1));
	env_var_setter(pwd, "OLDPWD", envp);
	ft_free(pwd);
	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH_LEN);
	ret = env_var_setter(pwd, "PWD", envp);
	ft_free(pwd);
	return (ret);
}

/// @brief 			Builtin cd command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
int	bi_cd(t_script *s, int n)
{
	// show_func(__func__, MY_START, ft_strjoin_free(ft_strdup("execute bi: "), ft_trdup(s->cmds[n].argv[0])));
	char	*home;
	int		status;

	env_var_setter(s->cmds[n].argv[s->cmds[n].argc - 1], "_", &s->envp);
	if (!s->cmds[n].argv[1])
	{
		home = env_var_getter("HOME", s->envp, NULL);
		if (home == NULL)
		{
			free(home);
			return (return_error("Minishell: cd: HOME not set", 1, 0));
		}
		status = change_dir(home, &s->envp);
		free(home);
		return (status);
	}
	if (s->cmds[n].argc > 2)
		return (return_error("Minishell: cd: too many arguments", 1, 0));
	if (s->cmds[n].argv[1][0] == '\0')
	{
		status = change_dir(".", &s->envp);
		return (status);
	}
	status = change_dir(s->cmds[n].argv[1], &s->envp);
	return (status);
}
