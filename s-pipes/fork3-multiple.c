/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:41:03 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/23 18:03:49 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


void	func0(int id1, int id2)
{
	pid_t	pidc;
	pid_t	pidp;

	pidc = getpid();
	pidp = getppid();
	printf("\n********* INIT (%d) : id1 = %d, id2 = %d\n", pidp, id1, id2);
}
void	func1(int id1, int id2)
{
	pid_t	pidc;
	pid_t	pidp;

	pidc = getpid();
	pidp = getppid();
	printf("\n********* CHILD 1 (%d)(%d) : id1 = %d, id2 = %d\n", pidp, pidc, id1, id2);
}

void	func2(int id1, int id2)
{
	pid_t	pidc;
	pid_t	pidp;

	pidc = getpid();
	pidp = getppid();
	printf("\n********* CHILD 2 (%d)(%d) : id1 = %d, id2 = %d\n", pidp, pidc, id1, id2);
}

void	func3(int id1, int id2)
{
	pid_t	pid;
	wait(NULL);

	pid = getpid();
	printf("\n********* PARENT (%d): id1 = %d, id2 = %d\n", pid, id1, id2);
}
int	main(void)
{
	int id1 = 10;
	int id2 = 10;

	func0(id1, id2);
	printf("\nbefore fork(1) *****************\n");
	printf("id1 = %d\n", id1);
	printf("id2 = %d\n", id2);
	id1 = fork();
	printf("\nafter fork(1) *****************\n");
	printf("id1 = %d\n", id1);
	printf("id2 = %d\n", id2);

	if (id1 == 0)
	{
		printf("\nChild process id1 %d\n", id1);
	}
	else
	{
		printf("\nbefore fork(2) *****************\n");
		printf("Process process id1 %d\n", id1);
		printf("Process process id2 %d\n", id2);
		id2 = fork();
		printf("after fork(2) *****************\n");
		printf("fork 2 process id1 %d\n", id1);
		printf("fork 2 process id2 %d\n", id2);
	}
	while (1)
	{
		if (id1 == 0 || id2 == 0)
		{
			if (id1 == 0)
				func1(id1, id2);
			else
				func2(id1, id2);
		}
		else if (id1 != 0 && id2 != 0)
		{
			func3(id1, id2);
		}
		sleep(1);
	}
	return 0;
}
