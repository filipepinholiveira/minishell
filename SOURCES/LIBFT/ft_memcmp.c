/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:14:47 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/11 20:19:12 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				valor;
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	i = 0;
	valor = 0;
	ptrs1 = (unsigned char *) s1;
	ptrs2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while ((ptrs1 || ptrs2) && ptrs1[i] == ptrs2[i] && i < n - 1)
		i++;
	if (ptrs1[i] > ptrs2[i])
		valor = 1;
	else if (ptrs1[i] < ptrs2[i])
		valor = -1;
	else if (ptrs1[i] == ptrs2[i])
		valor = 0;
	return (valor);
}
/*
int	main()
{
	char a[] = "Filipa";
	char b[] = "Filipe";
	char c[] = "Filipa";
	printf("%d\n", ft_memcmp(a, b, 6));
	printf("%d\n", ft_memcmp(b, a, 6));
	printf("%d\n", memcmp(c, a, 6));
	printf("%d\n", memcmp(a, b, 6));
}
*/
