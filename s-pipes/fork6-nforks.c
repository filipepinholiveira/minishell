/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork6-nforks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:41:03 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/23 22:48:16 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


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
	int id1 = fork();
	int id2 = fork();

	if (id1 == 0)
	{
		if (id2 == 0)
			printf("\nChild Child process id1->id2 [%d-%d]\n", id1, id2);
		else
			printf("\nParent Child process id1 %d\n", id1);
	}
	else
	{
		if (id2 == 0)
			printf("\n=> Parent Child process id1->id2 [%d->%d]\n", id1, id2);
		else
			printf("\n=> Parent process id1 %d\n", id1);
	}
	while (wait(NULL) != -1  || errno != ECHILD){
		printf("Waited for child process to finish %d\n", getpid());
	}
	return (0);
}
