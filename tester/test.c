/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:42:50 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/18 12:33:19 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc != 3)
		return (0);
	ft_printf("argv[1] = %s\n", argv[1]);
	argv[1] = ft_strrev(argv[1], 0);
	ft_printf("argv[1] = %s\n", argv[1]);
	ft_printf("argv[1] = %s\n", ft_strrev(argv[1], 0));
	ft_print(ft_strrev(argv[1], ft_atoi(argv[2])));
	return (0);
}
