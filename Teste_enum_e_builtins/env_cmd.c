/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:15 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/13 16:55:12 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int env_print(char **cmd, char **envp)
{
    int count = 0;

	(void)cmd;
    while (envp[count] != NULL)
    {
		printf("%s\n", envp[count]); // nao usar printf
        count++;
    }
    return (count);
}