/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:42:50 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/21 21:58:54 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	main(int argc, char **argv)
{
	char			*line;
	HIST_ENTRY		**hist_lst;
	HISTORY_STATE	*hist_state;
	char			input_str[MAXCOM];
	char			*parsed_args[MAXLIST];
	char			*parsed_args_piped[MAXLIST];
	int 			execFlag = 0;

	(void)argc;
	(void)argv;
	line = NULL;
	if (argc != 3)
		return (0);
	ft_printf("argv[1] = %s\n", argv[1]);
	argv[1] = ft_strrev(argv[1], 0);
	ft_printf("argv[1] = %s\n", argv[1]);
	ft_printf("argv[1] = %s\n", ft_strrev(argv[1], 0));
	ft_print(ft_strrev(argv[1], ft_atoi(argv[2])));

	hist_state = init_history();
	line = rl_gets(line);
	ft_printf("line = %s\n", line);

	init_shell();
	while (1)
	{
		// print shell line
		print_dir_path();
		// take input
		if (get_input(input_str))
			continue;
		// process
		execFlag = process_str(input_str, parsed_args, parsed_args_piped);
		// execflag returns zero if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// 2 if it is including a pipe.

		// execute
		if (execFlag == 1)
			exec_args(parsed_args);

		if (execFlag == 2)
			exec_args_piped(parsed_args, parsed_args_piped);
	}
	return (0);
}
