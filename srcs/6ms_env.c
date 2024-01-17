/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6ms_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/16 12:33:44 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 				This function prints the environment variables
/// @param envp			Environment variables
/// @return				void
void	show_envp(char **envp)
{
	show_func(__func__, MY_START, NULL);
	int i = -1;

	if (!envp)
		return ;
	while (envp[++i])
	{
		printf("envp[%i] = %s\n", i, envp[i]);
	}
	show_func(__func__, SUCCESS, NULL);
}

/// @brief 			This function gets the environment variable index
/// @param var 		variable to be found
/// @param envp 	Environment variables
/// @return			Index of the variable
int	env_var_index_getter(char *var, char **envp)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, var);
	//show_func(__func__, SHOW_MSG, *envp);
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
	printf("env_var_setter: %s = %s, env& =%p\n", var, val, *envx);
	int		index;
	char	*var_new;
	char	*old_record;

	var_new = ft_strjoin(var, "=");
	index = env_var_index_getter(var, *envx);
	printf("%s , index = %i\n",__func__, index);
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
		show_func(__func__, SHOW_MSG, (*envx)[0]);
		(*envx)[1] = NULL;
		return (0);
	}
	old_record = (*envx)[index];
	(*envx)[index] = ft_strjoin_free(var_new, ft_strdup(val));
	free(old_record);
	show_func(__func__, SUCCESS, (*envx)[index]);
	return (0);
}

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*env_var_getter(char *var, char **envp)
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
		printf("Variable '%s' not found\n", var);
		ret = ft_strdup("");
		if (!ret)
			return (NULL);
	}
	show_func(__func__, SUCCESS, ret);
	return (replace_multiple_space(ret));
}

/// @brief 		This function gets the environment variable name after a $ and
///				returns its corresponding value in the environment.
/// @param str	String to be parsed
/// @param envp	Environment variables
/// @param i	Index start
/// @return		replace variable
char	*replace_loop(char *str, char **envp, int *i)
{
	show_func(__func__, MY_START, NULL);
	char	*tmp;
	char	c;

	if (str[0] == '?')
	{
		(*i)++;
		if (g_exit_status >= 256)
			return (ft_itoa(WEXITSTATUS(g_exit_status)));
		else
			return (ft_itoa(g_exit_status));
	}
	if (ft_isspace(str[0]) || str[0] == '\'' || str[0] == '\"')
		return (ft_strdup("$"));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	c = str[*i];
	str[*i] = '\0';
	tmp = env_var_getter(str, envp); // envp_getter.c
	str[*i] = c;
	show_func(__func__, SUCCESS, NULL);
	return (tmp);
}

/// @brief 			Splits the string on '$' and accounts for the possibility
///					that the string may begin with a '$'
/// @param line_buf	String to be split
/// @param before	Pointer to the string before the first '$'
/// @param i		Index start
/// @return			Split string
char	**init_split_before(char *token, char **newToken, int *i)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("11 token = ", token));
	//show_func(__func__, SHOW_MSG, ft_strjoin("before   = ", *before));
	show_func(__func__, SHOW_MSG, ft_strjoin(ft_strjoin("12 i     = ",ft_itoa(*i)), "\n"));

	char	**split;

	split = ft_split(token, '$');
	if (token[0] && token[0] != '$')
	{
		*newToken = ft_strdup(split[0]);
		show_func(__func__, SHOW_MSG, ft_strjoin("21 [IF]   !$ newToken   = ", *newToken));

		(*i)++;
	}
	else
	{
		*newToken = ft_strdup("");
		show_func(__func__, SHOW_MSG, ft_strjoin("[22 ELSE] =$ newToken   = ", *newToken));
	}
	show_func(__func__, SUCCESS, ft_strjoin("31 token = ", token));
	show_func(__func__, SUCCESS, ft_strjoin("32 i     = ",ft_itoa(*i)));
	return (split);
}

/// @brief 				Replaces ARGS in a given string by the environment vars
///						by iterating through the string and replacing each
///						environment variable with its value.
/// @param line_buf		String to be parsed
/// @param envp			Environment variables
/// @param i			Index start
/// @param j			Index end
/// @return				String with ARGS replaced by envp vars
char	*replace_env_var(char *token, char **envp, int i, int j)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("\nTOKEN to EVALUATE = ", token));
	show_func(__func__, SHOW_MSG, envp[0]);

	char	**split;
	char	*newToken;
	char	*tmp;
	int k;

	newToken = NULL;
	printf("%s%s -> CALL%s\n",SBYLW, __func__, SRST);
	split = init_split_before(token, &newToken, &i);
	printf("%s%s -> CALL RETURN%s\n",SBYLW, __func__, SRST);
	show_func(__func__, SHOW_MSG, ft_strjoin("newToken   = ", newToken));
	k = -1;
	while (split[++k])
		printf("%s%s -> split[%d] = %s%s\n",SBHRED, __func__, k, split[k], SRST);
	show_func(__func__, SHOW_MSG, ft_strjoin("i        = ", ft_itoa(i)));
	while (split[i])
	{
		show_func(__func__, SHOW_MSG, "\nwhile check quotes");
		printf("%s i = %d, split[i] = %s%s\n", SBHRED, i, split[i], SRST);
		printf("%s%s -> CALL%s\n",SBYLW, __func__, SRST);
		if ((odd_before(split, i, '\'') && odd_after(split, i, '\''))
			&& (first_quote(token) || !(odd_before(split, i, '\"')
					&& odd_after(split, i, '\"'))))
		{
			show_func(__func__, SHOW_MSG, ft_strjoin("\n[IF]   1 newToken = ", newToken));
			newToken = ft_strjoin_free(newToken, ft_strjoin("$", split[i]));
			show_func(__func__, SHOW_MSG, ft_strjoin("\n[IF]   2 newToken = ", newToken));
		}
		else
		{
			j = 0;
			show_func(__func__, SHOW_MSG, ft_strjoin("\n[ELSE] 1 newToken = ", newToken));
			tmp = ft_strjoin_free(newToken, replace_loop(split[i], envp, &j));
			newToken = ft_strjoin(tmp, split[i] + j);
			show_func(__func__, SHOW_MSG, ft_strjoin("\n[ELSE] 2 newToken = ", newToken));
			free(tmp);
		}
		i++;
	}
	show_func(__func__, SHOW_MSG, ft_strjoin(" 1 -> ", newToken));

	if (token[ft_strlen(token) - 1] == '$')
		newToken = ft_strjoin_free(newToken, ft_strdup("$"));
	show_func(__func__, SHOW_MSG, ft_strjoin(" 2 -> ", newToken));
	free_split(split);
	show_func(__func__, SUCCESS, NULL);
	return (newToken);
}

/// @brief		This function replaces multiple spaces with a single space
/// @param str	String to be parsed
/// @return		String with multiple spaces replaced by a single space
char	*replace_multiple_space(char *str)
{
	show_func(__func__, MY_START, NULL);
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	split = ft_split_set(str, " \t\v\r\f\n");
	tmp = malloc(sizeof(char) * ft_strlen(str));
	if (!tmp)
		return (str);
	while (split[i])
	{
		if (i > 0)
			tmp = ft_strjoin_free(tmp, ft_strdup(" "));
		tmp = ft_strjoin_free(tmp, split[i]);
		i++;
	}
	free(split);
	free(str);
	show_func(__func__, SUCCESS, NULL);
	return (tmp);
}

