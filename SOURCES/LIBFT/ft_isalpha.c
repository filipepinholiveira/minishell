/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:09:50 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/09 14:57:19 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}
/*
** LIBRARY: <ctype.h>
** SYNOPSIS: alphabetic character test
**
** DESCRIPTION:
** 		The isalpha() function tests for any character for which isupper(3) or
**	islower(3) is true.
*/

/*
int     main()
{
    int a = 'f';
    int b = ' ';
    int c = '!';

    printf("%d\n", ft_isalpha(a));
    //write(1, "\n", 1);
    printf("%d\n", ft_isalpha(b));
    //write(1, "\n", 1);
    printf("%d\n", ft_isalpha(c));
    //write(1, "\n", 1);
}*/
