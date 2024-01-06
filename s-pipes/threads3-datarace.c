/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads3-datarace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:14:10 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/24 18:25:01 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int	mails = 0;

void	*routine(void *arg)
{
	int	i;

	i = -1;
	while (++i < 1000000)
	{
		mails++;
	}
}

int	main(int argc, char *argv[])
{
	pthread_t	p1;
	pthread_t	p2;
	pthread_t	p3;
	pthread_t	p4;

	if (pthread_create(&p1, NULL, &routine, NULL) != 0
		|| pthread_create(&p2, NULL, &routine, NULL) != 0
		|| pthread_create(&p3, NULL, &routine, NULL) != 0
		|| pthread_create(&p4, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(p1, NULL) != 0 || pthread_join(p2, NULL) != 0
		|| pthread_join(p3, NULL) != 0 || pthread_join(p4, NULL) != 0)
		return (2);
	printf("Number of mails: %d\n", mails);
	return (0);
}
