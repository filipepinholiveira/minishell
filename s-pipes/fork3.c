/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:41:03 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/22 20:01:17 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	int id = fork();

	printf("id = %d\n", id);
	// printf("id = %d\n", id);
	if (id != 0)
	{
		fork();
		printf("Parent process id %d\n", id);
	}
	// else
	// {
	// 	printf("Parent process id %d\n", id);
	// }
	return 0;
}