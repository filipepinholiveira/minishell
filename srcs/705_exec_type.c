/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   705_exec_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:25:54 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 21:25:22 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_equal_check(t_script *s, int n, int i)
{
	char	**new_array;
	int		j;

	 show_func(__func__, MY_START, NULL);
	j = 0;
	while (s->cmds[n].argv[i])
	{
		if (!ft_strchr(s->cmds[n].argv[i], '='))
		{
			new_array = malloc(sizeof(char *) * (s->cmds[n].argc - i + 1));
			while (s->cmds[n].argv[i])
				new_array[j++] = ft_strdup(s->cmds[n].argv[i++]);
			new_array[j] = NULL;
			s->cmds[n].argc = j;
			free_array(s->cmds[n].argv);
			s->cmds[n].argv = new_array;
			break ;
		}
		i++;
	}
	i = 0;
	if (exec_type(s->cmds[n].argv[i]) != CMD_EQ)
		return (exec_type(s->cmds[n].argv[0]));
	else
	{
		while (s->cmds[n].argv[i])
		{
			bi_apend_check (s, n, i);
			i++;
		}
		// printf("testo o bi_apend\n");
	}

	/* chamar a funçao if(exec_type = cmd_eq) --> bI_apend_check (s, n, 0) esse 0 é valido para exec_one) sao 15 linhas!!!!
	dentro do while
	en_var_getter criar val old, val novo --> if val null = ft_strdup("") 
	
	else : ft_strjoin(val old, val new)
	
	
	criar var --> temp=strjoin
	
	 */
	// show_func(__func__, SUCCESS, ft_strdup(s->cmds[n].argv[0])); 
	return (CMD_EQ);
}

/// @brief 			Detects the type of commando to execute : a builtin and
/// 				what kind builtin or a system comand CMD_EX
/// @param cmd 		Command to execute
/// @return 		Command id
int exec_type(char *cmd)
{
	// show_func(__func__, MY_START, NULL);
	int id;

	id = CMD_EX;
	if (ft_strchr(cmd, '='))
		id = CMD_EQ;
	else if (ft_strncmp(cmd, "echo", 5) == SUCCESS)
		id = CMD_ECHO;
	else if (ft_strncmp(cmd, "cd", 3) == SUCCESS)
		id = CMD_CD;
	else if (ft_strncmp(cmd, "pwd", 4) == SUCCESS)
		id = CMD_PWD;
	else if (ft_strncmp(cmd, "export", 7) == SUCCESS)
		id = CMD_EXPORT;
	else if (ft_strncmp(cmd, "unset", 6) == SUCCESS)
		id = CMD_UNSET;
	else if (ft_strncmp(cmd, "env", 4) == SUCCESS)
		id = CMD_ENV;
	else if (ft_strncmp(cmd, "exit", 5) == SUCCESS)
		id = CMD_EXIT;
	//show_func(__func__, SUCCESS, ft_itoa(id));
	return (id);
}


