/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2ms_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:38:24 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/13 23:14:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		Signal processing functions setter
/// @param		No parameter required
void	sig_setter(void)
{
	show_func(__func__, MY_START);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	show_func(__func__, SUCCESS);
}

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler(int signum)
{
	show_func(__func__, MY_START);
	if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		write(1, "\r", 1);
	}
	else if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
	show_func(__func__, SUCCESS);
}

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler_fork(int signum)
{
	show_func(__func__, MY_START);
	if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		write(1, "\r", 1);
	}
	else if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	show_func(__func__, SUCCESS);
}

/// @brief 			Handles the signal SIGINT when in heredoc
///					Exits with status 130 Command terminated by user
/// @param signum	The signal number
/// @return			void
void	sig_handler_heredoc(int signum)
{
	show_func(__func__, MY_START);
	if (signum == SIGINT)
		exit(130);
	show_func(__func__, SUCCESS);
}
