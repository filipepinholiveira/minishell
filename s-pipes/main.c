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
	int fd1 = dup(1);
	int fd2 = open("antonio.txt", O_WRONLY, O_CREAT, O_TRUNC, 0777);	// *i = 1;
	printf("fd2 = %d\n", fd2);
	write (fd2, "Hi\n", 3);
	write (fd2, "Hilll\n", 6);
	write (1, "Ola\n", 4);
	dup2(fd2, fd1); // vai escrever no fd2 o Hello
	close(fd2);

	write(fd1, "Hello1\n", 7);
	write(fd2, "Hello2\n", 7);
	close(fd1);
	close(1);
	write (1, "Ola\n", 4);
	//open(1);
	return (0);
}