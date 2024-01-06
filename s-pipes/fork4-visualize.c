/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:41:03 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/23 18:54:03 by antoda-s         ###   ########.fr       */
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
	int id = fork();
	int n;
	int i;
	if (id == 0)
	{
		n = 1;
	}
	else
	{
		n = 6;
		wait(NULL);
	}

	for(i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
	return 0;
}
