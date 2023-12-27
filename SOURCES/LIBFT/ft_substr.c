/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:01:07 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/14 20:22:00 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned int	p;

	if (s == 0)
		return (NULL);
	p = ft_strlen(s);
	if (start >= p)
		len = 0;
	ptr = malloc(((len + 1)) * (sizeof(char)));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (len))
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int	main()
{
	char a[] = "Filipe";
	printf("%s\n", a);
	char *ptr = a;
	ft_substr(ptr, 3, 3);
	printf("%p\n", ptr);
	printf("%s\n", ptr);
}
*/
