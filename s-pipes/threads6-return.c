#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*routine(void *i)
{
	int *k = malloc(sizeof(int));

	printf("runing thread %d\n", *(int *)i);
	sleep(3);
	printf("exiting thread %d\n", *(int *)i);
	*k = *(int *)i + 10;
printf("routine &k = %p\n", k);
printf("routine k = %d\n", *k);

	return ((void *)&k);
}

int	main(int argc, char *argv[])
{
	pthread_t	t1;
	pthread_t	t2;
	int i = 1;
	int j = 2;
	int *l;
	if (pthread_create(&t1, NULL, &routine, &i) != 0)
	{
		printf("error creating thread\n");
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine, &j) != 0)
	{
		printf("error creating thread\n");
		return (2);
	}
	printf("waiting for thread to finish...\n");
	if (pthread_join(t1, (void **)&l) != 0)
	{
		printf("error joining thread\n");
		return (3);
	}
printf("&k = %p\n", k);
printf("k = %d\n", *k);

	//i = *k;
	if (pthread_join(t2, (void **)&l) != 0)
	{
		printf("error joining thread\n");
		return (4);
	}
	//j = *k;
	printf("all threads finished, i = %d, j = %d\n", i, j);
	return (0);
}