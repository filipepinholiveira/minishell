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

/// @brief 		Calculate the length of a string
/// @param s	String
/// @return		The length of the string
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(const char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
}

int	main(void)
{
	char 	*msg[4];
	char	*inbuf;
	int		size[3];
	int		p[2];
	int		i;
	int		j;
	int	fd_out, fd_in;

	msg[0] = "hello,$world$#1";// ...\0
	msg[1] = "hall,$monde$#2";
	msg[2] = "ola,mundo$#3";
	msg[3] = NULL;
	if (pipe(p) < 0)
		exit(1);

	fd_in = p[0];
	fd_out = p[1];
	printf("p[0] = %d\n", fd_in);
	printf("p[1] = %d\n", fd_out);	i = -1;



	i = -1;
	while (++i < 3)
	{
		size[i] = ft_strlen(msg[i]);
		write(fd_out, msg[i], size[i] - 4);
	}
	// write(p[1], msg2, ft_strlen(msg2)+1);
	// write(p[1], msg3, ft_strlen(msg3)+1);
	// write(p[1], msg1, ft_strlen(msg1)+1);
	close(fd_out);
	
	*inbuf = '\0';
	read(fd_in, inbuf, 2);
	*(inbuf + 2) = '\0';
	printf("len = %d \n", ft_strlen(inbuf));
	printf("%s\n", inbuf);

	i = -1;
	while (++i < 3)
	{
		j = read(fd_in, inbuf, size[i]);
		*(inbuf + j) = '\0';
		printf("j = %d, %s\n", j, inbuf);
		*inbuf = '\0';
	}
	close(fd_in);
	return (0);
}
