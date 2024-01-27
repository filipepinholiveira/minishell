/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5ms_tk_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/25 15:39:34 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 				Creates a new token
/// @param string		String to be tokenized
/// @param size			Token size
/// @param type			Token type (as per enum t_token_type)
/// @return				New token
t_token	*tk_addnew(const char *string, int size, t_token_type type)
{
	t_token	*token;

	show_func(__func__, MY_START, NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_substr(string, 0, size);
	token->size = size;
	token->type = type;
	token->next = NULL;
	show_func(__func__, SUCCESS, NULL);
	return (token);
}

/// @brief 			Gets pointer to last node of token list
/// @param head		Pointer to token list
/// @return			last token list node
t_token	*tk_lst_last_getter(t_token *token_pointer)
{
	if (!token_pointer)
		return (NULL);
	while (token_pointer)
	{
		if ((*token_pointer).next == NULL)
			return (token_pointer);
		token_pointer = (*token_pointer).next;
	}
	return (token_pointer);
}

/// @brief 					Adds a new token to the end of the token list
/// @param token_lst		Pointer to token list
/// @param tk_addnew		Pointer to new token
void	tk_lst_addback(t_token **token_lst, t_token *tk_new)
{
	t_token	*token_lst_last;

	if (*token_lst)
	{
		token_lst_last = tk_lst_last_getter(*token_lst);
		(*token_lst_last).next = &*tk_new;
	}
	else
		*token_lst = tk_new;
}
