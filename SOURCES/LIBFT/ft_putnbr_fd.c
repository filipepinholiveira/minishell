/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:22:07 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/11/24 18:18:50 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	s;
	char	i;

	s = n;
	if (s < 0)
	{
		write(fd, "-", 1);
		s = -s;
	}
	if (s >= 10)
		ft_putnbr_fd(s / 10, fd);
	i = ((s % 10) + 48);
	write(fd, &i, 1);
}
/*
int main()
{
	int i = -1000;
	ft_putnbr_fd(i, 1);
}
*/
