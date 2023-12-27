/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:14:17 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/12 18:25:40 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	s = (s + i);
	if (c == '\0')
	{
		return ((char *)s + ft_strlen(s));
	}
	while (i > 0 && c != *s)
	{
		s--;
		i--;
	}
	if (c == *s)
	{
		return ((char *)s);
	}
	return (NULL);
}
/*
int	main()
{
	char	a[] = "Tiago Oliveira";
	printf("%s\n", ft_strrchr(a, 'O'));
}
*/
