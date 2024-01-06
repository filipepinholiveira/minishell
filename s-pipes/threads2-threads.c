/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2-threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:15:43 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/24 18:15:44 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void* routine() {
	x += 5;
	sleep(2);
	printf("Value of x: %d\n", x);
}

void* routine2() {
	sleep(2);
	printf("Value of x: %d\n", x);
}

int main(int argc, char* argv[]) {
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL)) {
		return 1;
	}
	if (pthread_create(&t2, NULL, &routine2, NULL)) {
		return 2;
	}
	if (pthread_join(t1, NULL)) {
		return 3;
	}
	if (pthread_join(t2, NULL)) {
		return 3;
	}
	return 0;
}