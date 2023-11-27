/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:42:50 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/27 13:19:24 by antoda-s         ###   ########.fr       */
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
	int 			exec_flag = 0;

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
		print_dir_path();
		if (get_input(input_str))
			continue;
		exec_flag = process_str(input_str, parsed_args, parsed_args_piped);
		// execute
		if (exec_flag == 1)
			exec_args(parsed_args);

		if (exec_flag == 2)
			exec_args_piped(parsed_args, parsed_args_piped);
	}
	return (0);
}
