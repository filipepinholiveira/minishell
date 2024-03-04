/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   505_tk_xpd_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/04 17:59:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @attention	>token builder< set of functions
/// @brief
/// @param ntk
/// @param s
/// @return
char	*tk_xpd_var_filler(char *ntk, t_script *s)
{
	int		i;
	char	*tmp;

	i = 1;
	// tmp = ntk;
	printf("%s : &ntk = %p\n",__func__, &ntk[0]);
	if (var_firstchar(ntk[i]) == SUCCESS)
	{
		if (*s->envt)
			tmp = env_var_getter(ntk + 1, s->envp, s->envt);
		tmp = env_var_getter(ntk + 1, s->envp, NULL);
		//printf("%s : env &ntk = %p, %s\n",__func__, ntk + 1, ntk + 1);
		//printf("%s : env &tmp = %p, %s\n",__func__, tmp, tmp);
	}
	else if (ntk[i] == '0')
		tmp = ft_strdup("minishell");
	else if (ft_isdigit(ntk[i]))
		tmp = ft_strdup("");
	else if (ntk[i] == '?' && g_exit_status >= 256)
		tmp = ft_itoa(WEXITSTATUS(g_exit_status));
	else if (ntk[i] == '?' && g_exit_status < 256)
		tmp = ft_itoa(g_exit_status);
	else if (ntk[i] == '$')
		tmp = ft_itoa(getpid());
	else if (!ntk[i])
		tmp = ft_strdup("$");
	else
	{
		printf("%s : else %s\n",__func__, ntk);
		// tmp = ft_strdup(ntk + 1);
		tmp = ft_strdup(ntk);
	}
	free(ntk);
	//printf("%s : tmp = %p\n", __func__, tmp);
	return (tmp);
}

/// @attention	>token builder< set of functions
/// @brief
/// @param ntk
/// @param s
/// @return
char	*tk_xpd_filler(char ***ntks, t_script *s)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup("");
	i = -1;
	while ((*ntks)[++i])
		printf("%s : ntks[%i] = \"%s\"\n",__func__, i, (*ntks)[i]);
	i = -1;
	while ((*ntks)[++i])
	{
		tmp2 = (*ntks)[i];
		if ((*ntks)[i][0] == '$' && ((*ntks)[i][1] || (*ntks)[i + 1]))
		{
			(*ntks)[i] = tk_xpd_var_filler(tmp2, s);
			if (!(*ntks)[i])
				(*ntks)[i] = ft_strdup("");
		}
		else
			(*ntks)[i] = tk_xpd_unquote(tmp2);
		tmp = ft_strjoin(tmp, (*ntks)[i]);
	}
	return (tmp);
}
