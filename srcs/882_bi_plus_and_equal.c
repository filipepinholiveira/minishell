

#include "minishell.h"

int bi_is_plus_equal(t_script *s, int n)
{
    show_func(__func__, MY_START, NULL);
    int i;

    if (!s->envp || !s->cmds[n].argv[0])
		return (ERROR);
    env_var_setter("","_", &s->envp);
    i = -1;
    

}
