/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:28:06 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/21 23:23:23 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

// ft_tokenize

//char *    ft_tokenize(char *input);
char	*ft_tokenize(const char *input, char **av, size_t *nbr_tokens);

// ft_strtok

char	*ft_strtok(char *src_str, char *delim);

//ft_execmd.c
void	ft_execmd(char **Token_list, int tokens_nbr);

//get_location.c

char	*get_location(char *command);

//ft_cd.c
int		cd_command(char **args);

#endif
