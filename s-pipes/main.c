# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>

int main(void)
{
	// int *i;
	// printf(" i = %d\n", *i);
	int fd1 = dup(STDOUT_FILENO);
	int fd2 = open("antonio.txt", O_WRONLY, O_CREAT, O_TRUNC, 0777);	// *i = 1;
	printf("fd1 = %d\n", fd1);
	printf("fd2 = %d\n", fd2);
	write (fd2, "Ola em fd2\n", 11);
	write (fd1, "Ola em fd1\n", 11);
	printf("BEFORE DUP2 fd1 = %d\n", fd1);
	printf("BEFORE DUP2 fd2 = %d\n", fd2);
	dup2(fd2, fd1); // vai escrever no fd2 o Hello
	//close(fd2);

	printf("AFTER DUP2 fd1 = %d\n", fd1);
	printf("AFTER DUP2 fd2 = %d\n", fd2);
	write (fd2, "Ala em fd2\n", 11);
	write (fd1, "Ala em fd1\n", 11);
	write (1, "Ola em STDOUT\n", 14);
	//open(1);
	close(fd1);
	close(fd2);

	return (0);
}