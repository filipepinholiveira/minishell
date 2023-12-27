/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:00:28 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/27 13:28:47 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 				Splits a string into an array of strings using a delimiter.
/// @param path 		String to be splited
/// @param delimiter 	character used as delimiter
/// @return 			String array containing splited string
char **split_path(char **path, char delimiter)
{
	size_t	count;
	size_t	i;
	size_t	j;
	size_t	start;
	char	*current;
	char	**result;

	// Conta o número de segmentos após a divisão
	count = 0;
	i = 0;

	// Encontrar o número total de segmentos
	while(path[i] != NULL)
	{
		current = path[i];
		while(*current != '\0')
		{
			if (*current == delimiter)
				count++;
			current++;
		}
		i++;
	}
	result = (char **)malloc(sizeof(char *) * (count + 1 +1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	// Loop para dividir cada string no array original
	while (path[i] != NULL) 
	{
		current = path[i];
		start = 0;

    	// Encontrar segmentos na string atual
    	while (*current != '\0') 
		{
			if (*current == delimiter) 
			{
				result[j] = ft_strdup(path[i] + start);
				if (result[j] == NULL) 
					return(NULL);
				j++;
				start = current - path[i] + 1;
			}
        	current++;
    	}

		// Adiciona o último segmento
		result[j] = strdup(path[i] + start);
		if (result[j] == NULL) 
			return(NULL);
		j++;
		i++;

		// Adiciona NULL para indicar o final do novo array
    	result[j] = NULL;
	}
	return (result);
}