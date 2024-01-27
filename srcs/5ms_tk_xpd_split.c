/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5ms_tk_xpd_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/26 18:22:39 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *tk_var_xpd_dolar(char *oToken, int *i)
{
	show_func(__func__, MY_START, NULL);
	int	j;

	j = *i;
	(*i)++;
	if (oToken[*i] && var_firstchar(oToken[*i]) == SUCCESS)
		while (oToken[*i] && var_name_checker(oToken[*i]) == SUCCESS)
			(*i)++;
	else if (oToken[*i] != '\"' && oToken[*i] != '\'')
		(*i)++;
	show_func(__func__, SUCCESS, NULL);
	return (ft_substr(oToken, j, *i - j));
}

static void	tk_var_xpd_dquote(char *oToken, char ***new_tk, int *splits, int *i)
{
	show_func(__func__, MY_START, NULL);
	int	j;
	int	xpd;

	xpd = 0;
	j = *i;
	(*i)++;
	while (oToken[*i] && oToken[*i] != '\"')
	{
		if (oToken[*i] == '$')
		{
			if (xpd == 0)
				(*new_tk)[(*splits)++] = ft_substr(oToken, j, *i - j);
			xpd = 1;
			(*new_tk)[(*splits)++] = tk_var_xpd_dolar(oToken, i);
			j = *i;
		}
		else
		{
			(*i)++;
			xpd = 0;
		}
	}
	(*i)++;
	(*new_tk)[*splits] = ft_substr(oToken, j, *i - j);
	show_func(__func__, SUCCESS, NULL);
}

void	tk_var_xpd_squote(char *oToken, char ***new_tk, int *splits, int *i)
{
	show_func(__func__, MY_START, NULL);
	int	j;

	j = *i;
	(*i)++;
	while (oToken[*i] && oToken[*i] != '\'')
		(*i)++;
	(*i)++;
	(*new_tk)[*splits] = ft_substr(oToken, j, *i - j);
	show_func(__func__, SUCCESS, NULL);
}

static void	tk_var_xpd_else(char *oToken, char ***new_tk, int *splits, int *i)
{
	show_func(__func__, MY_START, NULL);
	int	j;

	j = *i;
	(*i)++;
	while (oToken[*i] && oToken[*i] != '$'
		&& oToken[*i] != '\"' && oToken[*i] != '\'')
		(*i)++;
	(*new_tk)[*splits] = ft_substr(oToken, j, *i - j);
	show_func(__func__, SUCCESS, NULL);
}

static char	**tk_var_xpd_init(char *oToken)
{
	show_func(__func__, MY_START, NULL);
	int		j;
	char	**new_tk;
	int		splits;

	splits = tk_var_xpd_splits(oToken);
	new_tk = (char **)malloc(sizeof(char *) * (splits + 1));
	new_tk[splits] = NULL;
	j = -1;
	while (++j < splits)
		new_tk[j] = NULL;
	show_func(__func__, SUCCESS, NULL);
	return (new_tk);
}

//static char	**env_var_detector2(char *oToken, char **new_tk, int *i)
// static int	tk_var_xpd(char *oToken, char **new_tk)
char **tk_var_xpd(char *oToken)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("11 token = ", oToken));
	int		i;
	char	**new_tk;
	int		splits;

	new_tk = tk_var_xpd_init(oToken);
	splits = -1;
	i = 0;
	while (oToken[i])
	{
		splits++;
		if (oToken[i] == '$')
			new_tk[splits] = tk_var_xpd_dolar(oToken, &i);
		else if (oToken[i] == '\"')
			tk_var_xpd_dquote(oToken, &new_tk, &splits, &i);
		else if (oToken[i] == '\'')
			tk_var_xpd_squote(oToken, &new_tk, &splits, &i);
		else
			tk_var_xpd_else(oToken, &new_tk, &splits, &i);
	}
	show_func(__func__, SUCCESS, NULL);
	return (new_tk);
}
