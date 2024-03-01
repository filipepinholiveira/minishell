/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f03.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:11:26 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/14 17:32:33 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


em int	var_name_check(char *var)

	while (var[i] && var[i] != '=' && var[i] != '+'):

	bash: filipe++=123
	filipe++=123: command not found


	ms: filipe++=123 
	
	ms: echo $filipe++
	++
	
	ms: export filipe++

	ms: env | grep filipe++
	filipe++=123


	/*--------------------------------------------------------*/

	bash: export filipe++=teste
	-bash: export: `filipe++=teste: not a valid identifier

	ms: export filipe++=teste (cria a variavel)

	ms: env | grep filipe++
	filipe++=teste

	/*-----------------------------------------------------*/














	while (var[i] && var[i] != '='):


	bash: filipe++=123
	filipe++=123: command not found


	ms: filipe++=123
	Minishell: export: `filipe++=123': not a valid identifier



	/* --------------------------------------------------------- */


	bash: export filipe++=teste
	-bash: export: `filipe++=teste: not a valid identifier


	ms: export filipe++=teste
	Minishell: export: `filipe++=teste: not a valid identifier

















	while (var[i] && var[i] != '=')
		if (!ft_isalnum(var[i]) && var[i] != '_' && (var[i] == '+' && var[i + 1] != '='))


	bash: filipe++=123
	filipe++=123: command not found


	ms: filipe++=123
	Minishell: export: `filipe++=123': not a valid identifier


	/* ---------------------------------------------------------------- */


	bash: export filipe++=teste
	-bash: export: `filipe++=teste: not a valid identifier

	ms: export filipe++=teste
	Minishell: export: `filipe++=teste: not a valid identifier









void	bi_equal_new(t_script *s, int n, int i)
{
	if (ft_strncmp(s->cmds[n].argv[i - 1], "+", 1) == 0)
	{
		env_var_setter(ft_strchr(s->cmds[n].argv[i], '=') + 1,
			ft_substr(s->cmds[n].argv[i], 0,
				ft_strlen(s->cmds[n].argv[i])
				- ft_strlen(ft_strchr(s->cmds[n].argv[i], '='))),
			&s->envt);
	}
	else
	env_var_setter(ft_strchr(s->cmds[n].argv[i], '=') + 1,
			ft_substr(s->cmds[n].argv[i], 0,
				ft_strlen(s->cmds[n].argv[i])
				- ft_strlen(ft_strchr(s->cmds[n].argv[i], '+'))),
			&s->envt);
}









bash: filipe=123 --> cria variavel temporaria
ms: filipe=123 -- > cria variavel temporaria