
#include "minishell.h"

/// @brief 			Update EXISTING TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_upd(t_script *s, int n, int i)
{
	env_var_setter(ft_strchr(s->cmds[n].argv[i], '=') + 1,
		ft_substr(s->cmds[n].argv[i], 0,
			ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '='))),
		&s->envp);
}

/// @brief 			Creates NEW TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_new(t_script *s, int n, int i)
{
	char *var;
	char *val;

	var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	val = ft_strdup(ft_strchr(s->cmds[n].argv[i], '=') + 1);
	// env_var_setter(ft_strchr(s->cmds[n].argv[i], '=') + 1,
	// 	ft_substr(s->cmds[n].argv[i], 0,
	// 		ft_strlen(s->cmds[n].argv[i])
	// 		- ft_strlen(ft_strchr(s->cmds[n].argv[i], '='))),
	// 	&s->envt);
	env_var_setter(val, var, &s->envp);
	ft_free(var);
	ft_free(val);
}
int index_tp_getter(t_script *s, int n, int i)
{
	char *var;
	int index_tp;

	var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));

	index_tp = env_var_index_getter(var, s->envp);
	ft_free(var);
	return (index_tp);
}

void	bi_equal_not_apend(t_script *s, int n, int i)
{
    show_func(__func__, MY_START, NULL);
    int		index_tp;

    if (var_name_check(s->cmds[n].argv[i]) == SUCCESS)
		{
			index_tp = index_tp_getter(s, n, i);
			// index_tp = env_var_index_getter(ft_substr(s->cmds[n].argv[i], 0,
			// 			ft_strlen(s->cmds[n].argv[i])
			// 			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '='))),
			// 		s->envp);
			printf("%s%s : index_tp = %d%s\n",__func__, SBHGRN, index_tp, SRST);
			if (index_tp != -1)
				bi_equal_upd(s, n, i);
			else
				bi_equal_new(s, n, i);
        }
}
