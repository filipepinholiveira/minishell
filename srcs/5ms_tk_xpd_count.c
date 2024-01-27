/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5ms_tk_xpd_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/26 11:02:11 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	tk_var_xpd_dolar_c(char *oToken, int *i)
{
	show_func(__func__, MY_START, NULL);
	(*i)++;
	if (oToken[*i] && var_firstchar(oToken[*i]) == SUCCESS)
		while (oToken[*i] && var_name_checker(oToken[*i]) == SUCCESS)
			(*i)++;
	else if (oToken[*i] != '\"' && oToken[*i] != '\'')
		(*i)++;
	show_func(__func__, SUCCESS, NULL);
}

static void	tk_var_xpd_dquote_c(char *oToken, int *splits, int *i)
{
	show_func(__func__, MY_START, NULL);
	int	xpd;

	xpd = 0;
	(*i)++;
	while (oToken[*i] && oToken[*i] != '\"')
	{
		if (oToken[*i] == '$')
		{
			if (xpd == 0)
				(*splits)++;
			xpd = 1;
			tk_var_xpd_dolar_c(oToken, i);
			(*splits)++;
		}
		else
		{
			(*i)++;
			xpd = 0;
		}
	}
	(*i)++;
	show_func(__func__, SUCCESS, NULL);
}

static void	tk_var_xpd_squote_c(char *oToken, int *i)
{
	show_func(__func__, MY_START, NULL);
	(*i)++;
	while (oToken[*i] && oToken[*i] != '\'')
		(*i)++;
	(*i)++;
	show_func(__func__, SUCCESS, NULL);
}

static void	tk_var_xpd_else_c(char *oToken, int *i)
{
	show_func(__func__, MY_START, NULL);
	(*i)++;
	while (oToken[*i] && oToken[*i] != '$'
		&& oToken[*i] != '\"' && oToken[*i] != '\'')
		(*i)++;
	show_func(__func__, SUCCESS, NULL);
}

//static char	**env_var_detector2(char *oToken, char **nToken, int *i)
// static int	tk_var_xpd(char *oToken, char **nToken)
int	tk_var_xpd_splits(char *oToken)
{
	show_func(__func__, MY_START, NULL);
	int	i;
	int	splits;

	splits = -1;
	i = 0;
	while (oToken[i])// && oToken[i + 1])
	{
		splits++;
		if (oToken[i] == '$')
			tk_var_xpd_dolar_c(oToken, &i);
		else if (oToken[i] == '\"')
			tk_var_xpd_dquote_c(oToken, &splits, &i);
		else if (oToken[i] == '\'')
			tk_var_xpd_squote_c(oToken, &i);
		else
			tk_var_xpd_else_c(oToken, &i);
	}
	show_func(__func__, SUCCESS, ft_itoa(splits + 1));
	return (splits + 1);
}

