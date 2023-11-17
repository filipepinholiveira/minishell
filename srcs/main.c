/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:42:50 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/17 18:46:35 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/name.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_printf("argv[1] = %s\n", argv[1]);
	argv[1] = ft_strrev(argv[1], 0);
	ft_printf("argv[1] = %s\n", argv[1]);
	ft_printf("argv[1] = %s\n", ft_strrev(argv[1], 0));
	return (0);
}
