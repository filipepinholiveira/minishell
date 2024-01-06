/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork5-getpid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:41:03 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/23 22:23:45 by antoda-s         ###   ########.fr       */
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
	int id;
	printf("INIT  Current id [%06d],\t parent pid[%d], pid[%d]\n", id, getppid(), getpid());
	id = fork();
	sleep(1);
	printf("pos 1 Current id [%06d],\t parent pid[%d], pid[%d]\n", id, getppid(), getpid());
	if (id == 0){
		printf("sleep Current id [%06d],\t parent pid[%d], pid[%d]\n", id, getppid(), getpid());
		sleep(1);
	}
	printf("pos 2 Current id [%06d],\t parent pid[%d], pid[%d]\n", id, getppid(), getpid());
	int res = wait(NULL);
	if (res == -1) {
		printf("\nprew  Current id [%06d],\t parent pid[%d], pid[%d]\n", id, getppid(), getpid());
		printf("No children to wait for\n");
		printf("posw  Current id [%06d],\t parent pid[%d], pid[%d]\n", id, getppid(), getpid());

	}else{
		printf("\nprew  Current id [%06d],\t parent pid[%d], pid[%d]\n", id, getppid(), getpid());
		printf("Finished execution %d\n", res);
		printf("posw  Current id [%06d],\t parent pid[%d], pid[%d]\n", id, getppid(), getpid());
	}
	return 0;
}
