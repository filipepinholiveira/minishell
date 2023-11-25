/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   threads2-propcesses.c							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: antoda-s <antoda-s@student.42porto.com>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/24 18:16:12 by antoda-s		  #+#	#+#			 */
/*   Updated: 2023/11/24 18:16:13 by antoda-s		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	int x = 2;
	int pid = fork();
	if (pid == -1) {
		return 1;
	}

	if (pid == 0) {
		x++;
	}
	sleep(2);
	printf("Value of x: %d\n", x);
	if (pid != 0) {
		wait(NULL);
	}
	return 0;
}