/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:21:17 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/14 16:33:28 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*ptr;
	size_t		i;

	if (nmemb == '0' || size == '0')
	{
		return (NULL);
	}
	ptr = malloc((nmemb * size) * (sizeof(char)));
	if (ptr == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < (nmemb * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
/*
int	main()
{
	size_t nmemb = 3;
	size_t x = 4;
	char *str;


str = ft_calloc(nmemb, x);
printf("%p", str);
}
*/
