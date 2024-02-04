/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   503ms_tk_xpd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/03 20:43:46 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		This function gets the environment variable name after a $ and
///				returns its corresponding value in the environment.
/// @param str	String to be parsed
/// @param envp	Environment variables
/// @param i	Index start
/// @return		replace variable
// char	*replace_loop(char *str, char **envp, int *i)
// {
// 	show_func(__func__, MY_START, NULL);
// 	char	*tmp;
// 	char	c;

// 	if (str[0] == '?')
// 	{
// 		(*i)++;
// 		if (g_exit_status >= 256)
// 			return (ft_itoa(WEXITSTATUS(g_exit_status)));
// 		else
// 			return (ft_itoa(g_exit_status));
// 	}
// 	if (ft_isspace(str[0]) || str[0] == '\'' || str[0] == '\"')
// 		return (ft_strdup("$"));
// 	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
// 		(*i)++;
// 	c = str[*i];
// 	str[*i] = '\0';
// 	tmp = env_var_getter(str, envp);
// 	str[*i] = c;
// 	show_func(__func__, SUCCESS, NULL);
// 	return (tmp);
// }

/// @brief 			Splits the string on '$' and accounts for the possibility
///					that the string may begin with a '$'
/// @param line_buf	String to be split
/// @param before	Pointer to the string before the first '$'
/// @param i		Index start
/// @return			Split string
char	**tk_env_var_detector(char *oldToken, char **newToken, int *i)
{
	show_func(__func__, MY_START, ft_strjoin("11 token = ", oldToken));
	char	**split;

	split = ft_split(oldToken, '$');

	if (oldToken[0] && oldToken[0] != '$')
	{
		*newToken = ft_strdup(split[0]);
		(*i)++;
	}
	else
		*newToken = ft_strdup("");
	show_func(__func__, SUCCESS, ft_strjoin("31 newToken = ", *newToken));
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
	show_func(__func__, MY_START, NULL);
	if (ft_isalpha(c) || c == '_')
	{
		show_func(__func__, SUCCESS, NULL);
		return (SUCCESS);
	}
	show_func(__func__, ERROR, NULL);
	return (ERROR);
}

/// @brief 				Replaces ARGS in a given string by the environment vars
///						by iterating through the string and replacing each
///						environment variable with its value.
/// @param oldToken		Token String to be parsed
/// @param envp			Environment variables
/// @param i			Index start
/// @param j			Index end
/// @return				String with ARGS replaced by envp vars
// char	*env_var_expander(char *oldToken, char **envp, int i, int j)
char	*env_var_expander(char *oldToken, t_script *s)//char **envp)
{
	show_func(__func__, MY_START, "******************************************************************");
	show_func(__func__, SHOW_MSG, ft_strjoin("\nTOKEN to EVALUATE = ", oldToken));
	show_func(__func__, SHOW_MSG, s->envp[0]);


	char	**nToken;
	int k = 0;
	char *tmp1;

	nToken = NULL;
	nToken = tk_var_xpd(oldToken);
	printf("****************** NOW the LIST **************************\n");
	k = -1;
	while (nToken[++k])
		printf("%s%s -> &nToken = %p, nToken[%d] = %s%s\n",SBHYLW, __func__, nToken[k], k, nToken[k], SRST);
	printf("****************** NOW the STRING **************************\n");
	tmp1 = tk_xpd_filler(&nToken, s);
	show_func(__func__, SHOW_MSG, tmp1);
	free(nToken);

	show_func(__func__, SUCCESS, NULL);
	return (tmp1);
}

/// @brief		This function replaces multiple spaces with a single space
/// @param str	String to be parsed
/// @return		String with multiple spaces replaced by a single space
char	*replace_multiple_space(char *str)
{
	show_func(__func__, MY_START, str);
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	split = ft_split_set(str, " \t\v\r\f\n");
	tmp = malloc(sizeof(char) * ft_strlen(str));
	if (!tmp)
		return (str);
	tmp[0] = '\0';
	while (split[i])
	{
		if (i > 0)
			tmp = ft_strjoin_free(tmp, ft_strdup(" "));
		tmp = ft_strjoin_free(tmp, split[i]);
		i++;
	}
	free(split);
	free(str);
	show_func(__func__, SUCCESS, tmp);
	return (tmp);
}

