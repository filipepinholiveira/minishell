/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:12:19 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/10 16:29:04 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*a;

	a = s;
	i = 0;
	while (i < n)
	{
		a[i] = '\0';
		i++;
	}
}
/*
** LIBRARY: <strings.h>
** SYNOPSIS: write zeroes to a byte string
**
** DESCRIPTION:
** 		The bzero() function writes n zeroed bytes to the string s. If n is
**	zero, bzero() does nothing.
*/
/*
int	main()
{
	char	a[7] = " Filipe";
	size_t	n = 1;

	printf("Palavra e' %s\n", a);
	ft_bzero((void *) a, n);
	printf("Palavra e' %s\n", a);
	printf("Palavra e' %s\n", a + 1);
	printf("Palavra e' %c\n", a[4]);
}
*/
