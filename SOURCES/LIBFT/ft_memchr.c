/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:14:37 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/11 17:41:13 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptrx;

	i = 0;
	ptrx = ((char *)s);
	while (i < n)
	{
		if (ptrx[i] == c)
		{
			return (ptrx + i);
		}
		i++;
	}
	return (NULL);
}
/*
int	main()
{
char a[] = "Filipe";
printf("%s\n", a);
printf("%s\n", (char *)ft_memchr(a, 'l', 6));
}
*/
