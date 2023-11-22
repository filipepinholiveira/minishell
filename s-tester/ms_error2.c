/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:07:52 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/21 22:40:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_error(int error)
{
	if (error / CD_ERROR >= 1)
		return (print_error_cd(error));
	else if (error / EXEC_ERROR >= 1)
		return (print_error_exec(error));
	else if (error / FORK_ERROR >= 1)
		return (print_error_fork(error));
	else if (error / PROCESS_ERROR >= 1)
		return (print_error_process(error));
	else if (error / PIPE_ERROR >= 1)
		return (print_error_pipe(error));
	else if (error / FILE_ERROR >= 1)
		return (print_error_file(error));
	else if (error / MALLOC_ERROR >= 1)
		return (print_error_malloc(error));
	else if (error / ERROR >= 1)
		return (print_error_generic(error));
}

int	print_error_cd(int error)
{
		printf("\nChange directory error..");
	return (ms_free(void));
	return (error);
}

int	print_error_exec(int error)
{
	printf("\nCommand Exec error..");
	return (ms_free(void));
}

int	print_error_fork(int error)
{
	printf("\nFork error..");
	return (ms_free(void));
}

int	print_error_process(int error)
{
	printf("\nProcess error..");
	return (ms_free(void));
}

int	print_error_pipe(int error)
{
	if (error == ERROR_PIPE)
		printf("\nPipe error..");
	return (ms_free(void));
}

int	print_error_malloc(int error)
{
	printf("\nMalloc error..");
	return (ms_free(void));
}

int	print_error_generic(int error)
{
	printf("\nGeneric Error..");
	return (ms_free(void));
}

