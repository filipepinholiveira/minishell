/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:12:49 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/12 17:30:43 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*x;
	char	*y;

	i = 0;
	x = (char *) dest;
	y = (char *) src;
	if (!x && !y)
		return (0);
	while (i < n)
	{
		x[i] = y[i];
		i++;
	}
	return (x);
}
/*
int	main()
{
	char d[] = "Destination";
	char fonte[] = "xxxxxxx";
	printf("Destino mem antes %s\n", d);
	memcpy(d, fonte, 5);
	printf("Destino mem depois %s\n", d);
}
*/
