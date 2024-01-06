/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:42:50 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/22 12:28:15 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// C program to illustrate
// pipe system call in C
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MSGSIZE 16


int	main(void)
{
	char	*msg1 = "hello, world #1";
	char	*msg2 = "hallo, monde #2";
	char	*msg3 = "ola,   mundo #3";
	char	inbuf[MSGSIZE];
	int		p[2];
	int		i;
	int		j;

	if (pipe(p) < 0)
		exit(1);

	write(p[1], msg1, MSGSIZE);
	write(p[1], msg2, MSGSIZE);
	write(p[1], msg3, MSGSIZE);
	write(p[1], msg1, MSGSIZE);
	close(p[1]);
	i = -1;
	while (++i < 5)
	{
		j = read(p[0], inbuf, MSGSIZE);
		printf("j = %d, %s\n", j, inbuf);
		*inbuf = '\0';
	}
	return (0);
}
