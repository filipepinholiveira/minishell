/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:17:08 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/23 18:34:21 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	char	*ptr;
	int		i;

	if (!s)
		return ;
	ptr = s;
	i = 0;
	while (s[i])
	{
		f(i, &ptr[i]);
		i++;
	}
}
