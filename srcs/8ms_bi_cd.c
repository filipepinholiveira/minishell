/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8ms_bi_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:46 by fpinho-d          #+#    #+#             */
/*   Updated: 2024/01/09 00:22:29 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_env_var(char *var, char **envp)
{
	show_func(__func__, MY_START, NULL);
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var, envp[i], ft_strlen(var)) == SUCCESS)
			return (i);
		i++;
	}
	return (-1);
}
static int	set_env_var(char *val, char *var, char ***envp)
{
	show_func(__func__, MY_START, var);
	int		index;

	index = get_env_var(var, *envp);
	if (index == -1)
	{
		free(val);
		return (1);
	}
	free((*envp)[index]);
	(*envp)[index] = ft_strjoin_free(ft_strdup(var), val);
	return (0);
}

static int	change_dir(char *path, char ***envp)
{
	show_func(__func__, MY_START, path);
	int		ret;
	char	*pwd;

	ret = chdir(path);
	if (ret == -1)
		return (return_error(path, 1));
	set_env_var(get_env_ms("PWD", *envp), "OLDPWD=", envp);
	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH_LEN);
	ret = set_env_var(pwd, "PWD=", envp);
	return (ret);
}

/// @brief 			Builtin cd command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
int	bi_cd_cmd(t_command commands, char **envp)
{
	show_func(__func__, MY_START,
		ft_strjoin("execute bi: ", commands.argv[0]));
	char	*home;
	int		status;

	if (!commands.argv[1])
	{
		home = get_env_ms("HOME", envp);
		if (home == NULL)
		{
			ft_putendl_fd("Minishell: cd: HOME not set", 2);
			free(home);
			return (1);
		}
		status = change_dir(home, &envp);
		free(home);
		return (status);
	}
	if (commands.argv[2])
	{
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
		show_func(__func__, ERROR, NULL);
		return (1);
	}
	if (commands.argv[1][0] == '\0')
		return (change_dir(".", &envp));
	return (change_dir(commands.argv[1], &envp));
}

// {
// 	show_func(__func__, MY_START,
// 		ft_strjoin("execute bi: ", commands.argv[0]));
// 	char	*home;
// 	char	*special_path;
// 	int		i;

// 	i = 1;
// 	special_path = ft_strdup(commands.argv[i]);
// 	if (commands.argc > 2)
// 	{
// 		while (i < commands.argc && commands.argv[i + 1] != NULL)
// 		{
// 			special_path = ft_strjoin(special_path, " ");
// 			special_path = ft_strjoin(special_path, commands.argv[i + 1]);
// 			i++;
// 		}
// 		if (chdir(special_path) != 0)
// 		{
// 			printf("Minishell: cd: too many arguments\n");
// 			return (ERROR);
// 		}
// 		else
// 		{
// 			show_func(__func__, SUCCESS, NULL);
// 			return (SUCCESS);
// 		}
// 	}
// 	if (s->commands->argv[1] == NULL)
// 	{
// 		home = get_env_ms("HOME", envp);
// 		if (home == NULL)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 		if (chdir(home) != 0)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 	}
// 	else
// 	{
// 		if (chdir(s->commands->argv[1]) != 0)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 	}
// 	show_func(__func__, SUCCESS, NULL);
// 	return (SUCCESS);
// }

// ANTIGA SEM ARGUMENTO T_SCRIPT

// int	bi_cd_cmd(char **args)
// {
// 	show_func(__func__, MY_START, NULL);
// 	int		count;
// 	char	*home;

// 	count = arg_count(args);
// 	if (count > 2)
// 	{
// 		printf("Minishell: cd: too many arguments\n");
// 		return (ERROR);
// 	}
// 	if (args[1] == NULL)
// 	{
// 		home = getenv("HOME");
// 		if (home == NULL)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 		if (chdir(home) != 0)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 	}
// 	else
// 	{
// 		if (chdir(args[1]) != 0)
// 		{
// 			perror("Minishell: cd");
// 			return (ERROR);
// 		}
// 	}
// 	show_func(__func__, SUCCESS, NULL);
// 	return (SUCCESS);
// }
