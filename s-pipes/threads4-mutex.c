/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads4-mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:22:21 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/24 18:23:56 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*routine(void *a)
{
	int	i;

	i = -1;
	while (++i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int	main(int argc, char *argv[])
{
	pthread_t	p1;
	pthread_t	p2;
	pthread_t	p3;
	pthread_t	p4;

	if (pthread_mutex_init(&mutex, NULL) != 0)
		return (3);
	if (pthread_create(&p1, NULL, &routine, NULL) != 0
		|| pthread_create(&p2, NULL, &routine, NULL) != 0
		|| pthread_create(&p3, NULL, &routine, NULL) != 0
		|| pthread_create(&p4, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(p1, NULL) != 0 || pthread_join(p2, NULL) != 0
		|| pthread_join(p3, NULL) != 0 || pthread_join(p4, NULL) != 0)
		return (2);
	if (pthread_mutex_destroy(&mutex) != 0)
		return (4);
	printf("Number of mails: %d\n", mails);
	return (0);
}
