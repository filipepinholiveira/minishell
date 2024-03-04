/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   502_tk_xpd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 02:00:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @attention	>token builder< set of functions
/// @brief 		it takes a char sequence and counts the number of splits needed
///				to build an array based of the splitter char '\"',  '\'',  '$'
/// @param otk 	char sequance to evaluate
/// @return		number of splits needed to properly create an array
int	tk_var_xpd_splits_count(char *otk)
{
	int	i;
	int	splits;
	// show_func(__func__, MY_START, NULL);

	splits = -1;
	i = 0;
	while (otk[i])
	{
		splits++;
		if (otk[i] == '$')
			tk_var_xpd_dolar_c(otk, &i);
		else if (otk[i] == '\"')
			tk_var_xpd_dquote_c(otk, &splits, &i);
		else if (otk[i] == '\'')
			tk_var_xpd_squote_c(otk, &i);
		else
			tk_var_xpd_else_c(otk, &i);
	}
	return (splits + 1);
}

/// @attention	>token builder< set of functions
/// @brief 		Initializes the array of expanded token
///				1st it fecths nmumber of splits
/// 			2nd mallocs necessary memory
/// @param otk 	char sequence to be splited -> copied into the new created array
/// @return		pointer to the newly created array
char	**tk_var_xpd_init(char *otk)
{
	// int		j;
	char	**ntks;
	int		spl;

	spl = tk_var_xpd_splits_count(otk);
	ntks = ft_calloc(spl + 1, sizeof(char *));// * (spl + 1));
	if (!ntks)
	{
		return_error("", errno, 1);
		return (NULL);
	}
	ntks[spl] = NULL;
	// j = -1;
	// while (++j < spl)
	// 	ntks[j] = NULL;
	return (ntks);
}

/// @attention	>token builder< set of functions
/// @brief 		for each token type NAME it creates an array wich is the split
///				at '\'', '\"' and '$'
/// @param otk 	original token
/// @return		the token's array with expanded args
char	**tk_var_xpd(char *otk)
{
	int		i;
	char	**ntks;
	int		spl;
	// show_func(__func__, MY_START, NULL);

	ntks = tk_var_xpd_init(otk);
	printf("%s : (1) &ntks = %p\n", __func__, ntks);
	spl = -1;
	i = 0;
	while (otk[i])
	{
		spl++;
		if (otk[i] == '$')
			ntks[spl] = tk_var_xpd_dolar(otk, &i);
		else if (otk[i] == '\"')
			tk_var_xpd_dquote(otk, &ntks, &spl, &i);
		else if (otk[i] == '\'')
			tk_var_xpd_squote(otk, &ntks, &spl, &i);
		else
			tk_var_xpd_else(otk, &ntks, &spl, &i);
	}
	// show_func(__func__, SUCCESS, ft_strdup(*ntks));
	printf("%s : (2) &ntks = %p\n", __func__, ntks);
	return (ntks);
}

/// @attention	>token builder< set of functions
/// @brief 				Replaces ARGS in a given string by the environment vars
///						by iterating through the string and replacing each
///						environment variable with its value.
/// @param otk		Token String to be parsed
/// @param envp			Environment variables
/// @param i			Index start
/// @param j			Index end
/// @return				String with ARGS replaced by envp vars
char	*tk_env_var_expander(char *otk, t_script *s)
{
	char	**ntks;
	char	*res;
	// show_func(__func__, MY_START, NULL);

	ntks = NULL;
	ntks = tk_var_xpd(otk);
	res = tk_xpd_filler(&ntks, s);
	// show_func(__func__, SHOW_MSG, ft_strdup(*ntks));

	printf("%s : (X) &ntks = %p\n", __func__, ntks);
	//free_array(ntks);
	//free_array_name(ntks, "ntks");//**************************************
	// show_func(__func__, SUCCESS, ft_strdup(res));
	return (res);
}
