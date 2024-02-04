/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   505ms_tk_xpd_filler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/04 19:59:11 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/********* NEW FILE  *********/

char *tk_xpd_var_filler(char *new_tk_str, t_script *s)
{
	show_func(__func__, MY_START, new_tk_str);
	int		i;
	char	*tmp;

	i = 1;
	tmp = new_tk_str;
	if (var_firstchar(new_tk_str[i]) == SUCCESS)
		new_tk_str = env_var_getter(new_tk_str + 1, s->envp, s->envt);
	else if (ft_isdigit(new_tk_str[i]))
		new_tk_str = ft_strdup("");
	else if (new_tk_str[i] == '?' && g_exit_status >= 256)
		new_tk_str = ft_itoa(WEXITSTATUS(g_exit_status));
	else if (new_tk_str[i] == '?' && g_exit_status < 256)
		new_tk_str = ft_itoa(g_exit_status);
	else if (new_tk_str[i] == '$')
		new_tk_str = ft_itoa(getpid());
	else
		new_tk_str = ft_strdup(new_tk_str + 1);
	free(tmp);
	show_func(__func__, SUCCESS, new_tk_str);
	return (new_tk_str);
}



char	*tk_xpd_filler(char ***new_tk, t_script *s)//char **envp)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("11 token = ", (*new_tk)[0]));
	int		split;
	char	*tmp;

	tmp = ft_strdup("");
	split = -1;
	while ((*new_tk)[++split])
	{
		if ((*new_tk)[split][0] == '$'
			&& ((*new_tk)[split][1] || (*new_tk)[split + 1]))
				(*new_tk)[split] = tk_xpd_var_filler((*new_tk)[split], s);
		else
			(*new_tk)[split] = tk_xpd_unquote((*new_tk)[split]);
		tmp = ft_strjoin_free(tmp, (*new_tk)[split]);
	}
	return (tmp);
}
