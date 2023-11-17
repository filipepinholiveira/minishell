/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:21:20 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/17 17:22:26 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		reverts the order of an array contents
/// @param str	the array to revert
/// @param j	length of the array pointed by str
/// @return		the reverted array
char	*ft_strrev(char *str, int j)
{
	char	temp;
	int		i;

	i = 0;
	j = ft_strlen(str) - 1;
	if ((j - i) <= 0)
		return (str);
	while (i <= j)
	{
		temp = str[i];
		str[i++] = str[j];
		str[j--] = temp;
	}
	return (str);
}
