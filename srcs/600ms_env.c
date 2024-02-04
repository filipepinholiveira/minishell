/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600ms_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/03 20:51:48 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			This function gets the environment variable index
/// @param var 		variable to be found
/// @param envp 	Environment variables
/// @return			Index of the variable
int	env_var_index_getter(char *var, char **envp)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, var);
	int		index;

	if (!envp)
	{
		show_func(__func__, SHOW_MSG, "env array is NULL");
		return (-1);
	}
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(var, envp[index], ft_strlen(var)) == SUCCESS)
		{
			show_func(__func__, SUCCESS, ft_itoa(index));
			return (index);
		}
		index++;
	}
	return (-1);
}

/// @brief 				This function sets the environment variable
/// @param val 			Value to be set
/// @param var 			Variable to be set
/// @param envp 		Environment variables
/// @return 			0 if success, -1 if error
int	env_var_setter(char *val, char *var, char ***envx)
{
	show_func(__func__, MY_START, NULL);
	int		index;
	char	*var_new;
	char	*old_record;

	var_new = ft_strjoin(var, "=");
	index = env_var_index_getter(var, *envx);
	if (index == -1 && *envx)
	{
		index = 0;
		show_func(__func__, SHOW_MSG, (*envx)[index]);
		while ((*envx)[index])
			index++;
		(*envx)[index] = ft_strjoin_free(var_new, ft_strdup(val));
		(*envx)[index + 1] = NULL;
		show_func(__func__, SUCCESS, (*envx)[index]);
		return (0);
	}
	else if (index == -1 && !*envx)
	{
		*envx = malloc(sizeof(char *) * (1 + 1));
		(*envx)[0] = ft_strjoin_free(var_new, ft_strdup(val));
		show_func(__func__, SUCCESS, (*envx)[0]);
		(*envx)[1] = NULL;
		return (0);
	}
	old_record = (*envx)[index];
	(*envx)[index] = ft_strjoin_free(var_new, ft_strdup(val));
	free(old_record);
	show_func(__func__, SUCCESS, (*envx)[index]);
	return (0);
}



// {
// 	show_func(__func__, MY_START, var);
// 	char	*tmp;
// 	char	*ret;
// 	int		len;

// 	if (!envp)
// 		return (NULL);
// 	tmp = ft_strjoin(var, "=");
// 	len = ft_strlen(tmp);
// 	ret = NULL;
// 	while (*envp)
// 	{
// 		if (!ft_strncmp(tmp, *envp, len))
// 		{
// 			ret = ft_strdup(*envp + len);
// 			break ;
// 		}
// 		envp++;
// 	}
// 	free(tmp);
// 	if (!ret)
// 	{
// 		printf("Variable '%s' not found\n", var);
// 		ret = ft_strdup("");
// 		if (!ret)
// 			return (NULL);
// 	}
// 	printf("%s%s : %s = '%s' %s\n", SBHGRN, __func__, var, ret, SRST);
// 	//show_func(__func__, SUCCESS, ret);
// 	return (replace_multiple_space(ret));
// }

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
static char	*envp_var_getter(char *var, char **envp)
{
	show_func(__func__, MY_START, var);
	char	*tmp;
	char	*ret;
	int		len;

	if (!envp)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	ret = NULL;
	while (*envp)
	{
		if (!ft_strncmp(tmp, *envp, len))
		{
			ret = ft_strdup(*envp + len);
			break ;
		}
		envp++;
	}
	free(tmp);
	if (!ret)
	{
		printf("Variable '%s' not found @ envp\n", var);
		return (NULL);
	}
	printf("%s%s : %s = '%s' %s\n", SBHGRN, __func__, var, ret, SRST);
	return (ret);
}

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
static char	*envt_var_getter(char *var, char **envp)
{
	show_func(__func__, MY_START, var);
	char	*tmp;
	char	*ret;
	int		len;

	if (!envp)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	ret = NULL;
	while (*envp)
	{
		if (!ft_strncmp(tmp, *envp, len))
		{
			ret = ft_strdup(*envp + len);
			break ;
		}
		envp++;
	}
	free(tmp);
	if (!ret)
	{
		printf("Variable '%s' not found @ envt\n", var);
		return (NULL);
	}
	printf("%s%s : %s = '%s' %s\n", SBHGRN, __func__, var, ret, SRST);
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
	show_func(__func__, MY_START, NULL);
	char	*retp;
	char	*rett;

	retp = NULL;
	rett = NULL;
	if (envp)
		retp = envp_var_getter(var, envp);
	if (envt)
		rett = envt_var_getter(var, envt);
	if (!retp && !rett)
	{
		printf("Variable '%s' not found @ envp && @ envt\n", var);
		return (ft_strdup(""));
		return (retp);
	}
	else if (!retp && rett)
		return (rett);
	else if (retp)
		return (retp);
	show_func(__func__, ERROR, "error getting var");
	return (NULL);
}
