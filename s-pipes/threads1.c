#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*routine(void *i)
{
	printf("runing thread\n");
	sleep(3);
	printf("exiting thread\n");
	return (i + 10);
}

int	main(int argc, char *argv[])
{
	pthread_t	t1;

	pthread_create(&t1, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	return (0);
}