/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 22:33:15 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**env_del_one(char *del, char **envx)
{
	char	**new_array;
	char	*tmp;
	int		i;
	int		j;

	show_pointer(__func__, MY_START, del, envx);
	i = 0;
	while ((envx)[i])
		i++;
	new_array = ft_calloc(i, sizeof(char *));
	if (!new_array)
	{
		return_error("", errno, 1);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (envx[++i])
	{
		tmp = ft_substr(envx[i], 0, ft_strlen(envx[i])
				- ft_strlen(ft_strchr(envx[i], '=')));
		if (ft_strncmp(tmp, del, ft_strlen(tmp)) != SUCCESS)
		{
			new_array[j] = ft_strdup(envx[i]);
			j++;
		}
		free(tmp);
	}
	new_array[j] = NULL;
	free_array(envx);
	// free_array_name(envx, "env_del_one envx");
	return (new_array);
}

char 	**env_add_one(char **envx, char *new)
{
	char	**new_array;
	int		i;

	// show_func(__func__, MY_START, new);
	i = 0;
	while ((envx)[i])
		i++;

	// show_pointer(__func__, D_MALLOC, "old -> envx", envx);
	i = i + 2;
	new_array = ft_calloc(i, sizeof(char *));
	if (!new_array)
	{
		return_error("", errno, 1);
		return (NULL);
	}
	i = -1;
	while (envx[++i])
		new_array[i] = ft_strdup(envx[i]);
	new_array[i] = new;
	new_array[++i] = NULL;
	free_array(envx);
	return (new_array);
}

/// @brief 			This function gets the environment variable index
/// @param var 		variable to be found
/// @param envp 	Environment variables
/// @return			Index of the variable
int	env_var_index_getter(char *var, char **envx)
{
	show_pointer(__func__, MY_START, var, envx);
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
	//show_func(__func__, ERROR, ft_strdup("var not found"));
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
	char	*var_old;

	// show_func(__func__, MY_START, ft_strjoin_free(ft_strjoin_free(ft_strdup(var), ft_strdup("=")), ft_strdup(val)));
	if (!*envx)
		return (-1);
	if (val)
		var_new = ft_strjoin_free(ft_strjoin(var, "="), ft_strdup(val));
	else
		var_new = ft_strdup(var);
	i = env_var_index_getter(var, *envx);
	if (i == -1)// && *envx)
	{
		*envx = env_add_one(*envx, var_new);
		show_pointer(__func__, D_MALLOC, "new -> envx", (*envx));
	}
	// else if (i == -1 && !*envx)
	// {
	// 	*envx = malloc(sizeof(char *) * (1 + 1));
	// 	if (!*envx)
	// 	{
	// 		return_error("", errno, 1);
	// 		return (ERROR);
	// 	}
	// 	show_pointer(__func__, D_MALLOC, "init envx", *envx);
	// 	(*envx)[0] = var_new;
	// 	(*envx)[1] = NULL;
	// }
	else
	{

		if (ft_strncmp(var_new, (*envx)[i], ft_max(ft_strlen((*envx)[i]), ft_strlen(var_new))) != SUCCESS)
		{
			var_old = (*envx)[i];
			(*envx)[i] = var_new;
			ft_free(var_old);
		}
		else
		{
			free(var_new);
			var_new = NULL;
		}
	}
	// show_func(__func__, SUCCESS, ft_strdup(var));
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
	// show_func(__func__, MY_START, ft_strdup(var));

	if (!envx || !var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	ret = NULL;
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
	char	*ret;
	// show_func(__func__, MY_START, NULL);

	ret = envx_var_getter(var, envp);
	if (!ret)
		ret = envx_var_getter(var, envt);
	// printf("%sALERT!! %s%s : dupped : address = %s%p%s\n", SBHRED, SRST, __func__, SHBLU, ret, SRST);
	return (ret);
}
