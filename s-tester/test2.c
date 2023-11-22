/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:13:01 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/21 17:09:43 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

/// @brief 				Read a string, and return a pointer to it and add it to the history.
/// @param line_read	Pointer to the line to be read
/// @return				Pointer to the line read
char *rl_gets(void *line_read)
{
	/* If the buffer has already been allocated, return the memory to the free pool. */
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}

	/* Get a line from the user. */
	line_read = readline("Input your line:");

	/* If the line has any text in it, save it on the history. */

	if (line_read && *(char *)line_read)
		add_history(line_read);

	return (line_read);
}

HISTORY_STATE	*init_history(void)
{
	HISTORY_STATE	*hist_state;

	using_history();
	hist_state = history_get_history_state();
	hist_state->entries = NULL;
	hist_state->offset = 0;
	hist_state->length = 0;
	hist_state->size = 0;
	hist_state->flags = 0;
}

