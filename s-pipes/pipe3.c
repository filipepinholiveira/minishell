/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:02:22 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/23 13:02:23 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int	main(int argc, char *arg[])
{
	int	fd[2];
	int	id;
	int	x;
	int	y;

	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	printf("id = %d\n", id);
	if (id == 0)
	{
		printf("Child process\n");
		close(fd[0]);
		printf("1 - Child process\n");
		printf("Input a number: ");
		scanf("%d", &x);
		printf("2 - Child process\n");
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			perror("write error");
			exit(EXIT_FAILURE);
		}
		printf("3 - Child process\n");
		close(fd[1]);
		printf("4 - Child process\n");
	}
	else
	{
		printf("Parent process\n");
		close(fd[1]);
		printf("1 - Parent process\n");
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			perror("read error");
			exit(EXIT_FAILURE);
		}
		printf("2 - Parent process\n");
		close(fd[0]);
		printf("3 - Parent process\n");
		printf("Got y from child process= %d\n", y);
	}
	return (0);
}
