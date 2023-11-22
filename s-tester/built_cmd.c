/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:13:01 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/21 23:16:40 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

/// @brief 			Execute builtin command
/// @param parsed	Pointer to the command to be executed
/// @return			SUCCESS if the command is a builtin command or ERROR
int	built_cmd_handler(char **parsed)
{
	int		nb_built_cmds;
	int		built_cmd;
	int		i;
	char	**built_cmds[4];
	char	*username;

	nb_built_cmds = 4;
	built_cmd = 0;
	i = -1;
	built_cmds[0] = "exit";
	built_cmds[1] = "cd";
	built_cmds[2] = "help";
	built_cmds[3] = "hello";
	while (++i < nb_built_cmds)
	{
		if (ft_strcmp(parsed[0], built_cmds[i]) == 0)
		{
			built_cmd = i + 1;
			break ;
		}
	}
	return (build_cmd_exec(built_cmd, parsed));
}

/// @brief				Execute the command
/// @param built_cmd	Pointer to the command to be executed
/// @param parsed		Pointer to the command to be executed
/// @return				SUCCESS if the command is a builtin command or ERROR
int	built_cmd_exec(int built_cmd, char **parsed)
{
	if (built_cmd == 1)
	{
		printf("\nExiting..\n");
		exit(0);
	}
	else if (built_cmd == 2)
		return (cd_command(parsed[1]));
	else if (built_cmd == 3)
		return (show_help());
	else if (built_cmd == 4)
		return (show_hello());
	return (ERROR);
}

// int	process_str(char *str, char **parsed, char **parsed_pipe)
// {
// 	char	*piped_str[2];
// 	int		piped;

// 	piped = parse_pipe(str, piped_str);

// 	if (piped)
// 	{
// 		parse_space(piped_str[0], parsed);
// 		parse_space(piped_str[1], parsed_pipe);
// 	}
// 	else
// 		parse_space(str, parsed);

// 	if (built_cmd_exec(parsed))
// 		return 0;
// 	else
// 		return 1 + piped;
// }
