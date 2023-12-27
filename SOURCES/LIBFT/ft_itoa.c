/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:23:39 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/23 17:28:56 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static long	ft_countspaces(long n)
{
	long	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	i;
	long	k;

	k = n;
	i = ft_countspaces(k);
	ptr = (char *) malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	if (k == 0)
		ptr[0] = '0';
	if (k < 0)
	{
		k = -k;
		ptr[0] = '-';
	}		
	ptr[i--] = '\0';
	while (k > 0)
	{
		ptr[i] = (k % 10) + 48;
		k = (k / 10);
		i--;
	}
	return (ptr);
}
/*
int main()
{
	int valor = -2147483648;
	printf("number is %d\n", valor);
	printf("string is %s\n", ft_itoa(valor));
}
*/
