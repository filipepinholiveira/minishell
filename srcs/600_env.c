/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/04 18:03:04 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**env_del_one(char **envx, char *del)
{
	char	**new_array;
	char	*tmp;
	int		i;
	int		j;

	show_pointer(__func__, MY_START, del, envx);
	i = 0;
	while ((envx)[i])
		i++;
	printf("%s%s : previous size = [%d] %s\n", SBHYLW, __func__, i, SRST);
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
			printf("%s : %s%p%s : %p : 1 - new_array[%d] = %s%s\n", __func__, SHGRN, new_array + j, SBHYLW, new_array[j], j, new_array[j], SRST);
			j++;
		}
		free(tmp);
		//i++;
	}
	new_array[j] = NULL;
	printf("%s : %s%p%s : %p : 2 - new_array[%d] = %s%s\n", __func__, SHGRN, new_array + j, SBHYLW, new_array[j], j, new_array[j], SRST);
	// free_array(envx);
	free_array_name(envx, "env_del_one envx");
	// show_array(new_array, "envx added new");
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

	show_pointer(__func__, D_MALLOC, "old -> envx", envx);
	printf("%s%s : previous size = [%d] %s\n", SBHYLW, __func__, i, SRST);
	i = i + 2;
	new_array = ft_calloc(i, sizeof(char *));
	if (!new_array)
	{
		return_error("", errno, 1);
		return (NULL);
	}
	i = -1;
	while (envx[++i])
	{
		new_array[i] = ft_strdup(envx[i]);
		if (!i)
			printf("%s : %s%p%s : %p : first_item[%d] = %s%s\n", __func__,SHGRN, new_array + i,  SBHYLW, new_array[i], i, new_array[i], SRST);
		//i++;
	}
	new_array[i] = new;
	printf("%s : %s%p%s : %p :   new_item[%d] = %s%s\n", __func__, SHGRN, new_array + i,  SBHYLW, new_array[i], i, new_array[i], SRST);
	new_array[++i] = NULL;
	printf("%s : %s%p%s : %p          : terminator[%d] = %s%s\n", __func__, SHGRN, new_array + i,  SBHYLW, new_array[i], i, new_array[i], SRST);
	// free_array(envx);
	free_array_name(envx, "envx");
	// show_array(new_array, "envx add one");
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
		{
			printf("%s : %s%p%s : %p : envx[%i] = %s%s\n", __func__, SHGRN, envx + i, SHBLU, envx[i], i, envx[i], SRST);
			printf("%s%s : i = %d%s\n", SBHGRN, __func__, i, SRST);
			return (i);
		}
		i++;
	}
	//show_func(__func__, SHOW_MSG, ft_strdup("var not found"));
	printf("%s%s : i = %d%s\n", SBHGRN, __func__, -1, SRST);
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
	if (val)
		var_new = ft_strjoin_free(ft_strjoin(var, "="), ft_strdup(val));
	else
		var_new = ft_strdup(var);
	i = env_var_index_getter(var, *envx);
	if (i == -1 && *envx)
	{
		*envx = env_add_one(*envx, var_new);
		show_pointer(__func__, D_MALLOC, "new -> envx", (*envx));
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
		(*envx)[0] = var_new;
		// (*envx)[0] = ft_strjoin_free(var_new, ft_strdup(""));
		(*envx)[1] = NULL;
	}
	else
	{

		if (ft_strncmp(var_new, (*envx)[i], ft_max(ft_strlen((*envx)[i]), ft_strlen(var_new))) != SUCCESS)
		{
			var_old = (*envx)[i];
			printf("%s%s : %p : %s[%i] = %s%s\n", SHRED, __func__, (*envx)[i], "var_old", i, (*envx)[i], SRST);
			(*envx)[i] = var_new;
			printf("%s%s : %p : %s[%i] = %s%s\n", SHYLW, __func__, (*envx)[i], "var_new", i, (*envx)[i], SRST);
			// (*envx)[i] = ft_strjoin_free(var_new, ft_strdup(""));
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
	//int i;
	// show_func(__func__, MY_START, ft_strdup(var));

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
			printf("%s : *envx = %p, %s\n",__func__, *envx, *envx);
			ret = ft_strdup(*envx + len);
			printf("%s : *envx = %p, %s\n",__func__, ret, ret);
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
	// show_func(__func__, MY_START, NULL);

	retp = NULL;
	rett = NULL;
	if (envp)
		retp = envx_var_getter(var, envp);
	if (envt)
		rett = envx_var_getter(var, envt);
	if (!retp && !rett)
		return (NULL);
	else if (!retp && rett)
		return (rett);
	else if (retp)
		return (retp);
	return (NULL);
}
