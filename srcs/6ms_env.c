/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6ms_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/22 01:31:09 by antoda-s         ###   ########.fr       */
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
char	**tk_env_var_detector(char *oldToken, char **newToken, int *i)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("11 token = ", oldToken));
	//show_func(__func__, SHOW_MSG, ft_strjoin("before   = ", *before));
	show_func(__func__, SHOW_MSG, ft_strjoin(ft_strjoin("12 i     = ",ft_itoa(*i)), "\n"));
	int p = -1;
	char	**split;

	split = ft_split(oldToken, '$');
	while (split[++p])
		printf("%s%s -> split[%d] = %s%s\n",SBHRED, __func__, p, split[p], SRST);


	if (oldToken[0] && oldToken[0] != '$')
	{
		*newToken = ft_strdup(split[0]);
		show_func(__func__, SHOW_MSG, ft_strjoin("21 ********** if (token[0] && token[0] != '$') -> newToken = ", *newToken));
		(*i)++;
	}
	else // if (token[0] == '$')
	{
		*newToken = ft_strdup("");
		show_func(__func__, SHOW_MSG, ft_strjoin("[22 ********** else (token[0] == '$') -> newToken = ", *newToken));
	}
	show_func(__func__, SUCCESS, ft_strjoin("31 newToken = ", *newToken));
	show_func(__func__, SUCCESS, ft_strjoin("32 i     = ",ft_itoa(*i)));
	return (split);
}
int	var_name_checker(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (SUCCESS);
	return (ERROR);
}
int	var_firstchar(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (SUCCESS);
	return (ERROR);
}

// int	first_quote(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 			return (ERROR);
// 		i++;
// 	}
// 	return (SUCCESS);
// }
static int tk_var_xpd_splits(char *oToken)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("11 token = ", oToken));
	int i;
	int j;
	int slice = 0;
	int splits;

	splits = -1;
	i = 0;
	while (oToken[i] && oToken[i + 1])
	{
		printf("%s -> while 00 : oToken[%d] = %c\n",__func__, i, oToken[i]);
		j = i;
		if (oToken[i] == '$' && !var_firstchar(oToken[i + 1]))
		{
			splits++;
			printf("10 split = %d\n", splits);
			printf("%s%s -> 11 %s$VAR VALID = {%c, %c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], oToken[i + 1], SRST);
			j = i;
			i++;
			while (oToken[i] && !var_name_checker(oToken[i]))
				i++;
			printf("%s%s -> 13 %s$VAR VALID : show[%d] = %s%s\n", SBHRED, __func__, SBHGRN, splits, ft_substr(oToken, j, i - j), SRST);
		}
		else if (oToken[i] == '$' && var_firstchar(oToken[i + 1]) == ERROR)
		{
			splits++;
			printf("20 split = %d\n", splits);
			printf("%s%s -> 21 %s$VAR INVALID = {%c, %c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], oToken[i + 1], SRST);
			i++;
			printf("%s%s -> 212 %s$VAR INVALID : show[%d] = %s%s\n", SBHRED, __func__, SBHGRN, splits, ft_substr(oToken, j, i - j), SRST);
		}
		else if (oToken[i] == '\"')
		{
			splits++;
			printf("30 split = %d\n", splits);
			printf("%s%s -> 31 %s$DOUBLE QUOTE : detected = {%c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], SRST);
			j = i;
			i++;
			while (oToken[i] && oToken[i] != '\"')
			{
				printf("%s%s -> 311 %s$DOUBLE QUOTE : while = {%c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], SRST);
				if (oToken[i] == '$')
				{
					if (slice == 0)
					{
						printf("%s%s -> 312 %s$DOUBLE QUOTE SLICE : show[%d]   = %s%s\n", SBHRED, __func__, SBHGRN, splits, ft_substr(oToken, j, i - j), SRST);
						slice = 1;
					}
					splits++;
					printf("301 split = %d\n", splits);
					j = i;
					i++;
					if (var_firstchar(oToken[i]) == SUCCESS)
					{
						while (oToken[i] && var_name_checker(oToken[i]) == SUCCESS)
							i++;
						printf("%s%s -> 322 %s$DOUBLE QUOTE VAR VALID : show[%d]   = %s%s\n", SBHRED, __func__, SBHGRN, splits, ft_substr(oToken, j, i - j), SRST);
					}
					else
					{
						i++;
						printf("%s%s -> 332 %s$DOUBLE QUOTE VAR INVALID : show[%d]   = %s%s\n", SBHRED, __func__, SBHGRN, splits, ft_substr(oToken, j, i - j), SRST);
					}
					j = i;
					if (oToken[i] != '$')
					{
						splits++;
						printf("302 split = %d\n", splits);
					}
				}
				else
				{
					i++;
					if (slice)
					{
						slice = 0;
					}
				}

			}
			i++;
			printf("%s%s -> 342 %s$DOUBLE QUOTE END : show[%d]   = %s%s\n", SBHRED, __func__, SBHGRN, splits, ft_substr(oToken, j, i - j), SRST);
		}
		else if (oToken[i] == '\'')
		{
			splits++;
			printf("400 split = %d\n", splits);
			printf("%s%s -> 410 %s$SINGLE QUOTE detected = {%c, %c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], oToken[i + 1], SRST);
			j = i;
			i++;
			while (oToken[i] && oToken[i] != '\'')
				i++;
			i++;
			printf("%s%s -> 442 %s$SINGLE QUOTE : show[%d]   = %s%s\n", SBHRED, __func__, SBHGRN, splits, ft_substr(oToken, j, i - j), SRST);
		}
		else
		{
			splits++;
			printf("500 split = %d\n", splits);
			printf("%s%s -> 51 %s$NO VAR detected = {%c, %c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], oToken[i + 1], SRST);
			j = i;
			i++;
			while (oToken[i] && oToken[i] != '$' && oToken[i] != '\"' && oToken[i] != '\'')
				i++;
			printf("%s%s -> 522 %s$NO VAR FOUND : show[%d]   = %s%s\n", SBHRED, __func__, SBHGRN, splits, ft_substr(oToken, j, i - j), SRST);
		}
	}
	splits++;
	printf("%s%s -> 5 %s$splits = {%d}%s\n", SBHRED, __func__,
		SBHYLW, splits, SRST);
	show_func(__func__, SUCCESS, NULL);
	return (splits) ;
}
//static char	**env_var_detector2(char *oToken, char **nToken, int *i)
// static int	tk_var_xpd(char *oToken, char **nToken)
static char **tk_var_xpd(char *oToken)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("11 token = ", oToken));
	int i;
	int j;
	int slice = 0;
	char **nToken;
	int splits;

	nToken = NULL;
	splits = tk_var_xpd_splits(oToken);
	nToken = (char **)malloc(sizeof(char *) * (splits + 1));
	nToken[splits] = NULL;
	j = -1;
	while (++j < splits)
	{
		nToken[j] = NULL;
		// printf("nToken[%d] = %p\n", j, nToken[j]);
	}
	splits = -1;
	i = 0;
	while (oToken[i] && oToken[i + 1])
	{
		// printf("%s -> while 00 : oToken[%d] = %c\n",__func__, i, oToken[i]);
		j = i;
		if (oToken[i] == '$' && !var_firstchar(oToken[i + 1]))
		{
			splits++;
			// printf("%s%s -> 11 %s$VAR VALID = {%c, %c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], oToken[i + 1], SRST);
			j = i;
			i++;
			while (oToken[i] && !var_name_checker(oToken[i]))
				i++;
			nToken[splits] = ft_substr(oToken, j, i - j);
			// printf("%s%s -> 13 %s$VAR VALID : &nToken = %p, nToken[%d] = %s%s\n", SBHRED, __func__, SBHGRN, nToken[splits],splits, nToken[splits], SRST);
		}
		else if (oToken[i] == '$' && var_firstchar(oToken[i + 1]) == ERROR)
		{
			splits++;
			// printf("20 split = %d\n", splits);
			// printf("%s%s -> 21 %s$VAR INVALID = {%c, %c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], oToken[i + 1], SRST);
			i++;
			nToken[splits] = ft_substr(oToken, j, i - j);
			// printf("%s%s -> 211 %s$VAR INVALID : nToken[%d] = %s%s\n", SBHRED, __func__, SBHGRN, splits, nToken[splits], SRST);
		}
		else if (oToken[i] == '\"')
		{
			splits++;
			// printf("30 split = %d\n", splits);
			// printf("%s%s -> 31 %s$DOUBLE QUOTE : detected = {%c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], SRST);
			j = i;
			i++;
			while (oToken[i] && oToken[i] != '\"')
			{
				if (oToken[i] == '$')
				{
					if (slice == 0)
					{
						nToken[splits] = ft_substr(oToken, j, i - j);
						// printf("%s%s -> 311 %s$DOUBLE QUOTE SLICE : nToken[%d] = %s%s\n", SBHRED, __func__, SBHGRN, splits, nToken[splits], SRST);
						slice = 1;
					}
					splits++;
					// printf("301 split = %d\n", splits);
					j = i;
					i++;
					if (var_firstchar(oToken[i]) == SUCCESS)
					{
						while (oToken[i] && var_name_checker(oToken[i]) == SUCCESS)
							i++;
						nToken[splits] = ft_substr(oToken, j, i - j);
						printf("%s%s -> 321 %s$DOUBLE QUOTE VAR VALID : nToken[%d] = %s%s\n", SBHRED, __func__, SBHGRN, splits, nToken[splits], SRST);
					}
					else
					{
						i++;
						nToken[splits] = ft_substr(oToken, j, i - j);
						printf("%s%s -> 331 %s$DOUBLE QUOTE VAR INVALID : nToken[%d] = %s%s\n", SBHRED, __func__, SBHGRN, splits, nToken[splits], SRST);
					}
					j = i;
					if (oToken[i] != '$')
					{
						splits++;
						// printf("302 split = %d\n", splits);
					}
				}
				else
				{
					i++;
					if (slice)
					{
						slice = 0;
					}
				}
			}
			i++;
			nToken[splits] = ft_substr(oToken, j, i - j);
			// printf("%s%s -> 341 %s$DOUBLE QUOTE END : nToken[%d] = %s%s\n", SBHRED, __func__, SBHGRN, splits, nToken[splits], SRST);
			//splits++;
		}
		else if (oToken[i] == '\'')
		{
			splits++;
			// printf("400 split = %d\n", splits);
			// printf("%s%s -> 410 %s$SINGLE QUOTE detected = {%c, %c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], oToken[i + 1], SRST);
			j = i;
			i++;
			while (oToken[i] && oToken[i] != '\'')
				i++;
			i++;
			nToken[splits] = ft_substr(oToken, j, i - j);
			// printf("%s%s -> 421 %s$SINGLE QUOTE : nToken[%d] = %s%s\n", SBHRED, __func__, SBHGRN, splits, nToken[splits], SRST);
		}
		else
		{
			splits++;
			// printf("500 split = %d\n", splits);
			// printf("%s%s -> 51 %s$NO VAR detected = {%c, %c}%s\n", SBHRED, __func__, SBHYLW, oToken[i], oToken[i + 1], SRST);
			j = i;
			i++;
			while (oToken[i] && oToken[i] != '$' && oToken[i] != '\"' && oToken[i] != '\'')
				i++;
			nToken[splits] = ft_substr(oToken, j, i - j);
			// printf("%s%s -> 521 %s$NO VAR FOUND : nToken [%d]= %s%s\n", SBHRED, __func__, SBHGRN, splits, nToken[splits], SRST);
		}
	}
	// splits = -1;
	// while (nToken[++splits])
	// 	printf("%s%s -> nToken[%d] = %s%s\n",SBHYLW, __func__, splits, nToken[splits], SRST);
	show_func(__func__, SUCCESS, NULL);
	return (nToken) ;
	//return (split);
}

/// @brief 				Replaces ARGS in a given string by the environment vars
///						by iterating through the string and replacing each
///						environment variable with its value.
/// @param oldToken		Token String to be parsed
/// @param envp			Environment variables
/// @param i			Index start
/// @param j			Index end
/// @return				String with ARGS replaced by envp vars
char	*env_var_expander(char *oldToken, char **envp, int i, int j)
{
	show_func(__func__, MY_START, "******************************************************************");
	show_func(__func__, SHOW_MSG, ft_strjoin("\nTOKEN to EVALUATE = ", oldToken));
	show_func(__func__, SHOW_MSG, envp[0]);

	char	**split;
	char	*newToken;
	char	**nToken;
	char	*tmp;
	int k = 0;
	//char 	**splits;

	newToken = NULL;
	nToken = NULL;
	printf("%s%s -> 20 CALL%s\n",SBYLW, __func__, SRST);
	nToken = tk_var_xpd(oldToken);
	// tk_var_xpd(oldToken, &nToken, 0);
	printf("%s%s -> 20 CALL RETURN%s\n",SBYLW, __func__, SRST);
	k = -1;
	while (nToken[++k])
		printf("%s%s -> &nToken = %p, nToken[%d] = %s%s\n",SBHYLW, __func__, nToken[k], k, nToken[k], SRST);


	printf("%s%s -> 10 CALL%s\n",SBYLW, __func__, SRST);
	split = tk_env_var_detector(oldToken, &newToken, &i);
	printf("%s%s -> 10 CALL RETURN%s\n",SBYLW, __func__, SRST);
	k = -1;
	while (split[++k])
		printf("%s%s -> split[%d] = %s%s\n",SBHYLW, __func__, k, split[k], SRST);

	while (split[i])
	{
		printf("%s%s -> ******** while (split[i] = %s) ********%s\n", SBHRED, __func__, split[i], SRST);
		printf("%s%s -> 30 CALL%s\n",SBYLW, __func__, SRST);

		if ((odd_before(split, i, '\'') && odd_after(split, i, '\''))
			&& (first_quote(oldToken) || !(odd_before(split, i, '\"')
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
	if (oldToken[ft_strlen(oldToken) - 1] == '$')
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

