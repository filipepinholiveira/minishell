/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes4-n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:41:03 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/24 00:35:00 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define PROCESS_NUM 3

int	main(int argc, char **argv)
{
	int pids[PROCESS_NUM];
	int	pipes[PROCESS_NUM + 1][2];
	int i;
	int j;
	int x;

	i = -1;
	while (++i < PROCESS_NUM + 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	i =-1;

	int y = 5;
	printf("i = [P] write pipe[0][1] = %d\n", y);
	fflush(stdout);
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	close(pipes[0][1]);



	while (++i < PROCESS_NUM)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0){
			printf("\n[%d] child process created\n", i);
			fflush(stdout);
			j = -1;
			while (++j < PROCESS_NUM + 1)
			{
				if (j != i)
				{
					printf("i = [%d] A closing pipe[%d][0]\n", i, j);
					fflush(stdout);
					close(pipes[j][0]);
				}
				if (j != i + 1)
				{
					printf("i = [%d] B closing pipe[%d][1]\n", i, j);
					fflush(stdout);
					close(pipes[j][1]);
				}
			}
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}
			printf("i = [%d] read pipe[%d][0] = %d\n", i, i, x);
			fflush(stdout);
			x++;
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
			{
				perror("write");
				exit(EXIT_FAILURE);
			}
			printf("i = [%d] write pipe[%d][1] = %d\n", i, i + 1, x);
			fflush(stdout);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return (0);
			//break ;
		}
	}

	// int y =5;
	// printf("i = [P] write pipe[0][1] = %d\n", y);
	// fflush(stdout);
	// if (write(pipes[0][1], &y, sizeof(int)) == -1)
	// {
	// 	perror("write");
	// 	exit(EXIT_FAILURE);
	// }
	// close(pipes[0][1]);

	for (i = 0; i < PROCESS_NUM + 1; i++){
		wait(NULL);
	}

	if(read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	printf("\ni = [P] read pipe[%d][0] = %d\n", PROCESS_NUM, y);
	fflush(stdout);
	close(pipes[PROCESS_NUM][0]);

	return (0);
}
