/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1ms_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/16 12:14:25 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

/// @brief 		Creates array from system environment variables
/// @param envp system environment variables from main (... char **envp)
/// @return 	array copy of system environment variables
char	**envp_getter(char **envp)
{
	//show_func(__func__, MY_START, envp[0]);
	char	**ms_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ms_envp = malloc(sizeof(char *) * (i + 1));
	if (!ms_envp)
	{
		//show_func(__func__, ERROR, NULL);
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		ms_envp[i] = ft_strdup(envp[i]);
		if (!ms_envp[i])
		{
			//show_func(__func__, ERROR, NULL);
			return (NULL);
		}
			//show_func(__func__, SUCCESS, ft_strjoin(ft_strjoin(ft_itoa(i), " = "), ms_envp[i]));

		i++;
	}
	ms_envp[i] = NULL;
	//show_func(__func__, SUCCESS, NULL);
	return (ms_envp);
}

/// @brief 				Gets the terminal settings
/// @param termios_p	Pointer to the termios settings structure
void	termios_getter(struct termios *termios_p)
{
	show_func(__func__, MY_START, NULL);
	if (tcgetattr(STDIN_FILENO, termios_p) != 0)
		perror("tcgetattr() error");
	// else
	// {
	// 	if (termios_p->c_iflag & BRKINT)
	// 		show_func(__func__, SHOW_MSG, "BRKINT is set");
	// 	else
	// 		show_func(__func__, SHOW_MSG, "BRKINT is not set");
	// 	if (termios_p->c_cflag & PARODD)
	// 		show_func(__func__, SHOW_MSG, "Odd parity is used");
	// 	else
	// 		show_func(__func__, SHOW_MSG, "Even parity is used");
	// 	if (termios_p->c_lflag & ECHO)
	// 		show_func(__func__, SHOW_MSG, "ECHO is set");
	// 	else
	// 		show_func(__func__, SHOW_MSG, "ECHO is not set");
	// 	show_func(__func__, SHOW_MSG,
	// 		ft_strjoin(ft_strjoin("The end-of-file character is 0x",
	// 				ft_itoa(termios_p->c_cc[VEOF])), "\n"));
	// }
	show_func(__func__, SUCCESS, NULL);
}

void	termios_setter(struct termios *termios_p)
{
	show_func(__func__, MY_START, NULL);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, termios_p) != 0)
		perror("tcsetattr() error");
	// else
	// {
	// 	if (termios_p->c_iflag & BRKINT)
	// 		show_func(__func__, SHOW_MSG, "BRKINT is set");
	// 	else
	// 		show_func(__func__, SHOW_MSG, "BRKINT is not set");
	// 	if (termios_p->c_cflag & PARODD)
	// 		show_func(__func__, SHOW_MSG, "Odd parity is used");
	// 	else
	// 		show_func(__func__, SHOW_MSG, "Even parity is used");
	// 	if (termios_p->c_lflag & ECHO)
	// 		show_func(__func__, SHOW_MSG, "ECHO is set");
	// 	else
	// 		show_func(__func__, SHOW_MSG, "ECHO is not set");
	// 	show_func(__func__, SHOW_MSG,
	// 		ft_strjoin(ft_strjoin("The end-of-file character is 0x",
	// 				ft_itoa(termios_p->c_cc[VEOF])), "\n"));
	// }
	show_func(__func__, SUCCESS, NULL);
}

/// @brief 				Initializes the shell and keeps looping until exit
/// @param script		Script structure (see minishell struct)
/// @param line_buffer	Line buffer
/// @return				void
//int	ms_loop(t_script *s, char **line_buffer)
static int	ms_loop(t_script *s)
{
	show_func(__func__, MY_START, NULL);
	int		status;
	char	*line_buffer;

	line_buffer = NULL;
	while (1)
	{
		s->cmd_count = 0;
		signal_setter();
		status = parser(s, &line_buffer);
		ft_free_str(&line_buffer);
		if (status == 1)
			continue ;
		else if (status == 2)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (s->cmd_count > 0)
		{
			if (execute(s))
				break ;
		}
		//show_func(__func__, SHOW_MSG, ft_strjoin_free(ft_strdup("11 - s->cmd_count = "), ft_itoa(s->cmd_count)));
		free_commands(s->commands, s->cmd_count);
		//show_func(__func__,SHOW_MSG, ft_strjoin("12 - s->cmd_count = ", ft_itoa(s->cmd_count)));
	}
	if (s->cmd_count > 0)
	{
		//show_func(__func__, SHOW_MSG, ft_strjoin("21- s->cmd_count = ", ft_itoa(s->cmd_count)));
		free_commands(s->commands, s->cmd_count);
		//show_func(__func__, SHOW_MSG, ft_strjoin("22 s->cmd_count = ", ft_itoa(s->cmd_count)));
	}
	show_func(__func__, SHOW_MSG, "MSG = SUCCESS");
	return (0);
}

/// @brief 			Main function MINISHELL
/// @param argc		Number of arguments (NOT USED)
/// @param argv		Arguments (NOT USED)
/// @param envp		Environment variables
/// @return
int	main(int argc, char **argv, char **envp)
{
	show_func(__func__, MY_START, NULL);
	t_script	s;

	(void)argc;
	(void)argv;
	s.envp = envp_getter(envp);
	s.envt = NULL;
	termios_getter(&s.termios_p);
	ms_loop(&s);
	free_envp(s.envp);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
