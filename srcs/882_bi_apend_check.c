

#include "minishell.h"

char 	* bi_apend_check(t_script *s, int n, int i)
{
    show_func(__func__, MY_START, NULL);
    printf("str s->cmds[n].argv[i]: %s\n", s->cmds[n].argv[i]);

    printf("must apend\n");
    char *var;
    char *var_old;
    char *var_new;
    char *var_total;

    var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i]) - ft_strlen(ft_strchr(s->cmds[n].argv[i], '+')));
    // if (var != NULL)
    //     printf("str var para fazer env_getter: %s\n", var);
    var_old = env_var_getter(var, s->envp, s->envt);
    if (var_old == NULL)
        var_old = ft_strdup("");
    //printf("str var_old, o que estava antes: %s\n", var_old);
    var_new = ft_substr(s->cmds[n].argv[i], ft_strlen(var) + 2, ~
        ft_strlen(s->cmds[n].argv[i]) 
            - ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
    // if (var_new != NULL)
    //     printf("str var_new, conteudo da nova: %s\n", var_new);    
    var_total = ft_strjoin(var_old, var_new);
    // if (var_total != NULL)
    //     printf("str var_total, o que está na concatenaçao: %s\n", var_total);
    if (var)
        free (var);
    if (var_old)
        free(var_old);
    if (var_new)
        free(var_new);
    return (var_total);
}
