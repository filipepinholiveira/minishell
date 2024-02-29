/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/29 00:08:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			This function gets the environment variable index
/// @param var 		variable to be found
/// @param envp 	Environment variables
/// @return			Index of the variable
int	env_var_index_getter(char *var, char **envx)
{
	show_func(__func__, MY_START, NULL);
	int		i;

	if (!envx)
		return (-1);
	i = 0;
	while (envx[i])
	{
		if (ft_strncmp(var, envx[i], ft_strlen(var)) == SUCCESS)
			return (i);
		i++;
	}
	//show_func(__func__, SHOW_MSG, ft_strdup("var not found"));
	return (-1);
}

/// @brief 				This function sets the environment variable
/// @param val 			Value to be set
/// @param var 			Variable to be set
/// @param envp 		Environment variables
/// @return 			0 if success, -1 if error
int	env_var_setter(char *val, char *var, char ***envx)
{
	int		i;
	char	*var_new;
	char	*old_record;
	char	**new_array;
	show_func(__func__, MY_START, ft_strdup(var));

	if (val)
		var_new = ft_strjoin_free(ft_strjoin(var, "="), ft_strdup(val));
	else
		var_new = ft_strdup(var);
	i = env_var_index_getter(var, *envx);
	if (i == -1 && *envx)
	{
		i = 0;
		while ((*envx)[i])
			i++;
		show_pointer(__func__, D_MALLOC, "old -> envx -> ", (*envx));
		printf("%s%s : previous size = [%d] %s\n", SBHYLW, __func__, i, SRST);
		new_array = ft_calloc(i + 2, sizeof(char *));
		if (!new_array)
		{
			return_error("", errno, 1);
			return (ERROR);
		}
		show_pointer(__func__, D_MALLOC, "new -> envx -> ", new_array);
		i = -1;
		while ((*envx)[++i])
		{
			new_array[i] = ft_strdup((*envx)[i]);
			printf("%s%s :new_array[%d] = %s%s\n", SBHYLW, __func__, i, new_array[i], SRST);
		}
		new_array[i] = ft_strjoin_free(var_new, ft_strdup(""));
		printf("%s%s :*new_array[%d] = %s%s\n", SBHYLW, __func__, i, new_array[i], SRST);
		new_array[i + 1] = NULL;
		printf("%s%s :*new_array[%d] = %s%s\n", SBHYLW, __func__, i+1, new_array[i+1], SRST);
		show_pointer(__func__, D_FREE, "old -> envx -> ", (*envx));

		free_array(*envx);
		*envx = new_array;
		show_pointer(__func__, D_MALLOC, "new -> envx -> ", (*envx));
		show_array(*envx, "envx");
	}
	else if (i == -1 && !*envx)
	{
		*envx = malloc(sizeof(char *) * (1 + 1));
		if (!*envx)
		{
			return_error("", errno, 1);
			return (ERROR);
		}
		show_pointer(__func__, D_MALLOC, "init envx", *envx);
		(*envx)[0] = ft_strjoin_free(var_new, ft_strdup(""));
		(*envx)[1] = NULL;
	}
	else
	{
		old_record = (*envx)[i];
		(*envx)[i] = ft_strjoin_free(var_new, ft_strdup(""));
		free(old_record);
	}
	show_func(__func__, SUCCESS, ft_strdup(var));
	return (SUCCESS);
}

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*envx_var_getter(char *var, char **envx)
{
	char	*tmp;
	char	*ret;
	int		len;
	//int i;
	show_func(__func__, MY_START, ft_strdup(var));

	if (!envx || !var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	ret = NULL;
	//i = -1;
	while (*envx)
	{
		if (!ft_strncmp(tmp, *envx, len))
		{
			ret = ft_strdup(*envx + len);
			break ;
		}
		envx++;
	}
	free(tmp);
	if (!ret)
		return (NULL);
	return (ret);
}

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*env_var_getter(char *var, char **envp, char **envt)
{
	char	*retp;
	char	*rett;
	show_func(__func__, MY_START, NULL);

	retp = NULL;
	rett = NULL;
	if (envp)
	{

		show_func(__func__, SHOW_MSG, ft_strdup("envp calling"));
		retp = envx_var_getter(var, envp);
		show_func(__func__, SHOW_MSG, ft_strdup("envp return"));
	}
	if (envt)
	{
		show_func(__func__, SHOW_MSG, ft_strdup("envt calling"));
		rett = envx_var_getter(var, envt);
		show_func(__func__, SHOW_MSG, ft_strdup("envt return"));
	}
	if (!retp && !rett)
		return (NULL);
	else if (!retp && rett)
		return (rett);
	else if (retp)
		return (retp);
	return (NULL);
}
