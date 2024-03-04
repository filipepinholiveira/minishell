/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   840_bi_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:46:39 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:13:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		Test validity of shell variables name
/// @param var	Variable name to be tested
/// @return		SUCCESS or ERROR
int	var_name_check(char *var)
{
	 show_func(__func__, MY_START, NULL);
	int	i;

	i = 0;
	// show_func(__func__, SHOW_MSG, ft_strdup(var));
	if (var[i] && (!ft_isalpha(var[i]) || var[i] == '_'))
		return (ERROR);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && (var[i] == '+' && var[i + 1] != '='))
		{
			//show_func(__func__, ERROR, NULL);
			return (ERROR);
		}
		i++;
	}
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief  	Update the value of an existing variable either at envt or envp
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @param i 	Index of argument to be checked
void	bi_export_upd_var(t_script *s, int n, int i)
{
	 show_func(__func__, MY_START, NULL);
	char	*val;
	char	*var;

	show_array(s->envp, "1 bi_export_upd_var envp");

	var = ft_substr(s->cmds[n].argv[i], 0,
			ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	printf("%s : var -> %s\n", __func__, var);
	//show_func(__func__, SHOW_MSG, ft_strjoin("var -> ", var));
	val = ft_strchr(s->cmds[n].argv[i], '=') + 1;
	printf("%s : val -> %s\n", __func__, val);
	//show_func(__func__, SHOW_MSG, ft_strjoin("val -> ", val));

	env_var_setter(val, var, &s->envp);
	if (env_var_index_getter(var, s->envt) != -1)
		bi_unset_envt(s, n);
	//show_func(__func__, SUCCESS, NULL);
}

/// @brief  	Checks if export NEW environment variables or update existing
/// 			variables and also if the variables exist already in environment
/// 			temporary array
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @param i 	Index of argument to be checked
void	bi_export_new_var(t_script *s, int n, int i)
{
	 show_func(__func__, MY_START, NULL);
	char	*val;
	char	*var;
	int		j;

	var = s->cmds[n].argv[i];
	printf("%s : 1 - var -> %s\n", __func__, var);
	show_pointer(__func__, SHOW_MSG, "envp", s->envp);
	j = env_var_index_getter(var, s->envp);
	if (j >= 0)
	{
		printf("%s : \t\t 2 -EXPORT VAR EXISTS ALREADY IN P : rec @ envp -> %s\n", __func__,s->envp[j]);
		return ;
	}
	show_pointer(__func__, SHOW_MSG, "envt", s->envt);
	j = env_var_index_getter(var, s->envt);
	if (j >= 0)
	{
		printf("%s : \t\t 3 - EXPORT VAR EXIST IN T : var @ envt -> %s\n", __func__,s->envt[j]);
		val = env_var_getter(var, NULL, s->envt);
		printf("%s : \t\t 4 - EXPORT VAR val IN T : val @ envt = '%s'\n", __func__, val);
		env_var_setter(val, var, &s->envp);
		s->envt = env_del_one(s->envt, var);
		//bi_unset_envt(s, n);
	}
	else
		env_var_setter(NULL, var, &s->envp);
	show_pointer(__func__, D_MALLOC, "envp", s->envp);
	show_pointer(__func__, D_MALLOC, "envt", s->envt);
	//show_func(__func__, SUCCESS, NULL);
}
void	export_print(char *str)
{
	char	*s1;
	char	*s2;

	if (!(str[0] == '_' && str[1] == '='))
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (!ft_strchr(str, '='))
			ft_putstr_fd(str, STDOUT_FILENO);
		else
		{
			s2 = ft_strjoin_free(ft_strdup(ft_strchr(str, '=') + 1),
					ft_strdup("\""));
			s1 = ft_strjoin_free(ft_substr(str, 0, ft_strlen(str)
						- ft_strlen(s2) + 1), ft_strdup("\""));
			ft_putstr_fd(s1, STDOUT_FILENO);
			ft_putstr_fd(s2, STDOUT_FILENO);
			ft_free(s1);
			ft_free(s2);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int	export_status(t_script *s, int n)
{
	int		i;
	char	**order;

	if (!s->cmds[n].argv[1])
	{
		if (!s->envp)
			return (1);
		order = envp_init(s->envp);
		order = ordered_array(order, '=', 0, 0);
		i = -1;
		while (order[++i])
			export_print(order[i]);
		// free_array(order);
		free_array_name(order, "order");
	}
	else if (s->cmds[n].argv[1][0] == '\0')
		return (return_error("Syntax error", 1, 2));
	// show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 			Export PERMANENT environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_export(t_script *s, int n)
{
	 show_func(__func__, MY_START, NULL);
	int	i;

	// show_array(s->envp, "1 bi_export envp");
	if (!s->envp || !s->cmds[n].argv[1] || !s->cmds[n].argv[1][0])
	{
		if (export_status(s, n))
			return (1);
		// show_array(s->envp, "2 bi_export envp");
		return (0);
	}
	i = 1;
	while (s->cmds[n].argv[i])
	{
		if (var_name_check(s->cmds[n].argv[i]) == SUCCESS)
		{
			if (ft_strchr(s->cmds[n].argv[i], '='))
				bi_export_upd_var(s, n, i);
			else
				bi_export_new_var(s, n, i);
		}
		else
			export_error(s->cmds[n].argv[i], 1);
		i++;
	}
	// show_array(s->envp, "3 bi_export envp");
	// show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 		Alphatecially ordered array
/// @param src 	Array to order
/// @return 	Ordered array
char	**ordered_array(char **d, char t, int n, int j)
{
	int	i;
	int	len_i;
	int	len_j;
	int	res_cmp;

	 show_func(__func__, MY_START, ft_strdup("Ordering Array..."));
	while (d[n] && d[n + 1])
	{
		j = n;
		i = j;
		while (d[++j])
		{
			len_i = ft_strchr(d[i], t) - d[i];
			len_j = ft_strchr(d[j], t) - d[j];
			res_cmp = ft_strncmp(d[i], d[j], ft_min(len_i, len_j));
			if (res_cmp > 0 || (res_cmp == 0 && len_i > len_j))
				i = j;
		}
		ft_strswap(&d[n++], &d[i]);
	}
	// show_func(__func__, SUCCESS, ft_strdup("Array ordered..."));
	return (d);
}
