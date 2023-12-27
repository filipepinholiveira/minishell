/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:17:24 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/30 19:03:24 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static size_t	ft_countwords(char const *s1, char c)
{
	int		flag;
	size_t	i;
	size_t	count;

	i = 0;
	flag = 1;
	count = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			flag = 1;
		if (s1[i] != c && s1[i])
		{
			if (flag == 1)
			{
				count++;
				flag = 0;
			}
		}
		i++;
	}
	return (count);
}

static char	*ft_fillstring(char const *s, char c, size_t *i)
{
	size_t	start;

	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	size;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	size = ft_countwords(s, c);
	ptr = ((char **) malloc ((size + 1) * sizeof(char *)));
	if (!ptr)
		return (NULL);
	while (s[i] && k < size)
	{
		ptr[k] = ft_fillstring(s, c, &i);
		k++;
	}
	ptr[k] = NULL;
	return (ptr);
}
/*
int main()

{
	char s1[] = "||||filipe|||Oliveira||9";
	char **split = ft_split(s1, '|');
	for(size_t i = 0; i < ft_countwords(s1, '|');i++)
		printf("%s\n", split[i]);
}
*/
