/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:53:58 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/27 23:37:43 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @see		ft_isspace, ft_issign, ft_isdigit
/// @brief 		Converts the initial portion of the string pointed to by nptr
///				to long int
/// @param nptr	The string to convert
/// @return		The converted long int
long	ft_atol(const char *nptr)
{
	int			signal;
	long int	number;

	signal = 1;
	number = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (ft_issign(*nptr))
		signal *= ft_issign(*nptr++);
	while (ft_isdigit(*nptr))
		number = number * 10 + (*nptr++ - '0');
	return (number * signal);
}
/// @see		ft_isspace, ft_issign, ft_isdigit
/// @brief 		Converts the initial portion of the string pointed to by nptr
///				to long int
/// @param nptr	The string to convert
/// @return		The converted long int
long double	ft_atoll(const char *nptr)
{
	long double	signal;
	long double	number;

	signal = 1.0;
	number = 0.0;
	while (ft_isspace(*nptr))
		nptr++;
	if (ft_issign(*nptr))
		signal *= (long double)ft_issign(*nptr++);

	// printf("signal code at atoll = %Lf\n", (signal));

	while (ft_isdigit(*nptr))
		number = number * 10.0 + (long double)(*nptr++ - '0');
	// printf("number code before signal at atoll = %Lf\n", (number));
	number *= signal;
	// printf("number code after signal at atoll = %Lf\n", (number));
	// if (signal > 0)
	// 	printf("number - 922...at atoll = %Lf\n", number - __LONG_LONG_MAX__);
	// if (number > 9223372036854775806.0 || number < -9223372036854775808.0)
	// 	printf("exit code tested at atoll = %Lf\n", (number));
	return (number);
}
