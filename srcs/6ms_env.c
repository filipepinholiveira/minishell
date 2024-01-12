/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6ms_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/11 17:02:07 by antoda-s         ###   ########.fr       */
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
	show_func(__func__, SHOW_MSG, *envp);
	int		index;

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
int	env_var_setter(char *val, char *var, char ***envp)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, var);
	show_func(__func__, SHOW_MSG, val);
	show_func(__func__, SHOW_MSG, **envp);
	int		index;
	char *var_t1;

	printf("%s&envp = %p%s\n", SBHPPL, *envp, SRST);
	var_t1 = ft_strjoin(var, "=");
	// malloc var_t1
	printf("*envp = %p\n", *envp);
	index = env_var_index_getter(var, *envp);
	if (index == -1)
	{
		index = 0;
		while ((*envp)[index])
			index++;
		(*envp)[index] = ft_strjoin_free(var_t1, ft_strdup(val));
		// malloc (*envp)[index]: free(var_t1), free(malloc(strdup(val)))
		// = var_t1 > z: val> valor: reesultado (*envp)[index] = var_t1 val
		(*envp)[index + 1] = NULL;
		show_func(__func__, SUCCESS, (*envp)[index]);
		return (0);
	}
	(*envp)[index] = ft_strjoin_free(var_t1, ft_strdup(val));
	show_func(__func__, SUCCESS, (*envp)[index]);
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
	{
		show_func(__func__, ERROR, "envp is NULL");
		return (NULL);
	}
	show_func(__func__, SHOW_MSG, var);
	show_func(__func__, SHOW_MSG, *envp);
	printf("%s&envp = %p%s\n", SBHPPL, envp, SRST);
	if (!envp)
	{
		show_func(__func__, ERROR, "envp is NULL");
		return (NULL);
	}
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
		{
			show_func(__func__, MALLOC_ERROR, "ret is NULL");
			return (NULL);
		}
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
char	**init_split_before(char *line_buf, char **before, int *i)
{
	show_func(__func__, MY_START, NULL);
	char	**split;

	split = ft_split(line_buf, '$');
	if (line_buf[0] && line_buf[0] != '$')
	{
		*before = ft_strdup(split[0]);
		(*i)++;
	}
	else
		*before = ft_strdup("");
	show_func(__func__, SUCCESS, NULL);
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
char	*replace_env_var(char *line_buf, char **envp, int i, int j)
{
	show_func(__func__, MY_START, NULL);
	char	**split;
	char	*before;
	char	*tmp;

	before = NULL;
	split = init_split_before(line_buf, &before, &i);
	while (split[i])
	{
		if ((odd_before(split, i, '\'') && odd_after(split, i, '\''))
			&& (first_quote(line_buf) || !(odd_before(split, i, '\"')
					&& odd_after(split, i, '\"'))))
			before = ft_strjoin_free(before, ft_strjoin("$", split[i]));
		else
		{
			j = 0;
			tmp = ft_strjoin_free(before, replace_loop(split[i], envp, &j));
			before = ft_strjoin(tmp, split[i] + j);
			free(tmp);
		}
		i++;
	}
	if (line_buf[ft_strlen(line_buf) - 1] == '$')
		before = ft_strjoin_free(before, ft_strdup("$"));
	free_split(split);
	show_func(__func__, SUCCESS, NULL);
	return (before);
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

