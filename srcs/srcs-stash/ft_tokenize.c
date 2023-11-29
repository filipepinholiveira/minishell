/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_tokenize.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: antoda-s <antoda-s@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/09/08 03:21:19 by fpinho-d		  #+#	#+#			 */
/*   Updated: 2023/11/27 09:43:02 by antoda-s		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

/* a funçao tokenize vai receber uma string com o input do utilizador, e vai ter que calcular
quantas palavras recebeu o input, separa-las por tipo (command, built in, pipe, special char, et),
para serem tratadas ou executadas*/

/* a funçao tokenize vai receber uma string com o input do utilizador, e vai ter que calcular
quantas palavras recebeu o input, separa-las por tipo (command, built in, pipe, special char, et),
para serem tratadas ou executadas*/

#include "../include/minishell.h"

char	*ft_tokenize(const char *input, size_t *tokens_nbr)
{
	size_t i = 0;
	char * input_copy = NULL;
	char **token_list = NULL;

	input_copy = ft_strdup((char *)input);
	char *token = ft_strtok((char *)input, " ");
	while (token != NULL)
	{
		*tokens_nbr += 1;
		token = ft_strtok(NULL, " ");
	}
	token_list = (char **)malloc(sizeof(char *) * (*tokens_nbr) + 1);
	token_list[*tokens_nbr] = NULL;
	token = ft_strtok(input_copy, " ");
	i = -1;
	while (++i < *tokens_nbr && token != NULL)
	{
			token_list[i] = ft_strdup(token);
			token = ft_strtok(NULL, " ");
	}
	ft_execmd(token_list, *tokens_nbr);
	free(input_copy);
	//free(input); af testinfg
	return (token);
}

