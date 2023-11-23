/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:02:22 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/22 20:17:35 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *arg[])
{
	
	int	fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	int id = fork();
	if (id == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			perror("write error");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
	}
	else
	{
		int y;
		close(fd[1]);
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			perror("read error");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		printf("Got y from child process= %d\n", y);
	}
	return (0);
}
