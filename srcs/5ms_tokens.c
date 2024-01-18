/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5ms_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/17 20:00:37 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		This function is here to treat off cases where a $ expansion
///				would lead to empty name tokens with the exception for an empty
///				token after a pipe.
/// @param head Head of the token list
/// @return		clean content
void	remove_blank_tokens(t_token *head)
{
	t_token	*tmp;

	show_func(__func__, MY_START, NULL);
	while (head)
	{
		if (head->type != TK_PIPE && head->next && !head->next->content[0])
		{
			tmp = head->next->next;
			free(head->next->content);
			free(head->next);
			head->next = tmp;
		}
		else
			head = head->next;
	}
	show_func(__func__, SUCCESS, NULL);
}

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
	/*************************************************************************/
	// printf("%s-> token created = token->content = '%s%s%s'%s\n",
	// 	SBHPPL, SBWHT, token->content, SBHPPL, SRST);
	// printf("%s-> token created = token->size = '%s%d%s'%s\n",
	// 	SBHPPL, SBWHT, token->size, SBHPPL, SRST);
	// printf("%s-> token created = token->type = '%s%d%s'%s\n",
	// 	SBHPPL, SBWHT, token->type, SBHPPL, SRST);
	/*************************************************************************/
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

/// @brief 			Searches for a token type by token char set
/// @param s		String to be searched for token char set
/// @return			Struct with token type information: token char set, size
///					and token type
t_ops	tk_type_getter(const char *s)
{
	show_func(__func__, MY_START, NULL);
	t_ops		blank;
	int			i;
	const t_ops	ops[13] = {{">>", 2, TK_R_OUT}, {"<<", 2, TK_R_IN},
	{"|", 1, TK_PIPE}, {">", 1, TK_R_OUT}, {"<", 1, TK_R_IN},
	{" ", 1, TK_WS}, {"\n", 1, TK_WS}, {"\v", 1, TK_WS},
	{"\t", 1, TK_WS}, {"\r", 1, TK_WS}, {"\f", 1, TK_WS},
	{NULL, 1, 0},{NULL, 1, 0}};
	//{"=", 1, TK_EQUAL}, {NULL, 1, 0}};

	blank = (t_ops){0, 0, 0};
	i = -1;
	while (ops[++i].op)
	{
		if (!ft_strncmp(s, ops[i].op, ops[i].size))
		{
			show_func(__func__, SUCCESS,
				ft_strjoin("TOKEN found: ", (char *)ops[i].op));
			return (ops[i]);
		}
	}
	show_func(__func__, ERROR, "TOKEN NOT found");
	return (blank);
}

/// @brief 				Initializes the tk_getter
/// @param str			String to be tokenized
/// @param head			Head of the token list
/// @return				1 if success, 0 if error
int	tk_getter(char *str, t_token **tk_lst)
{
	show_func(__func__, MY_START, NULL);
	t_ops	ptr;
	char	*prev;

	prev = str;
	while (str && *str)
	{
		ptr = tk_type_getter(str);
		/*********************************************************************/
		// printf("str = '%s%s%s'\n", SBHYLW, str, SRST);
		// printf("ptr.op = '%s%s%s'\n", SBHYLW, ptr.op, SRST);
		// printf("ptr.size = '%s%d%s'\n", SBHYLW, ptr.size, SRST);
		// printf("ptr.type = '%s%d%s'\n", SBHYLW, ptr.type, SRST);
		/*********************************************************************/
		if (ptr.op != 0 && prev != str)
		{
			//printf("%s1-> token found = '%s'%s\n", SBHPPL, ptr.op, SRST);
			tk_lst_addback(tk_lst, tk_addnew(prev, str - prev, TK_NAME));
		}
		if (ptr.op != 0)
		{
			//printf("%s2-> token found = '%s'%s\n", SBHPPL, ptr.op, SRST);
			str += ptr.size;
			if (ptr.type != TK_WS)
				tk_lst_addback(tk_lst, tk_addnew(ptr.op, ptr.size, ptr.type));
			prev = str;
		}
		else if ((*str == '\"' || *str == '\'') && !closed_quotes_check(&str))
		{
			show_func(__func__, ERROR, ft_strjoin("quotes found", str));
			return (ERROR);
		}
		else
			++str;
	}
	if (prev != str)
	{
		//printf("%s3-> token found = '%s'%s\n", SBHPPL, ptr.op, SRST);
		tk_lst_addback(tk_lst, tk_addnew(prev, str - prev, TK_NAME));
	}
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

void show_token_list(t_token *token)
{
	t_token *tk_ptr;

	tk_ptr = token;
	printf("%s*****************************%s\n", SBHGRN, SRST);
	while (tk_ptr)
	{
		printf("%s-> token->content = '%s%s%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->content, SBHPPL, SRST);
		printf("%s-> token->size = '%s%d%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->size, SBHPPL, SRST);
		printf("%s-> token->type = '%s%d%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->type, SBHPPL, SRST);
		printf("%s*****************************%s\n", SBHGRN, SRST);
		tk_ptr = tk_ptr->next;
	}
}

/// @brief 				Trims the token command from whitespaces
/// @param line_buffer	string input with script
/// @param head			pointer to the head of the token list
/// @param script		script structure
/// @return				SUCCESS if valid, ERROR if invalid
int	tk_builder(char **line, t_token **token, t_script *s)
{
	show_func(__func__, MY_START, NULL);
	t_token	*tk_ptr;
	char	*content;

	if (tk_getter(*line, token) == ERROR)
	{
		show_func(__func__, ERROR, NULL);
		return (return_error("Syntax Error", 0));
	}
	show_token_list(*token);
	tk_ptr = *token;
	while (tk_ptr)
	{
		content = tk_ptr->content;
		printf("%s%s -> CALL%s\n",SBYLW, __func__, SRST);
		tk_ptr->content = env_var_expander(content, s->envp, 0, 0);
		printf("%s%s -> CALL RETURN%s\n",SBYLW, __func__, SRST);
		printf("%s-> content = '%s%s%s'%s\n",
			SBHPPL, SBWHT, content, SBHPPL, SRST);
		printf("%s-> token->content = '%s%s%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->content, SBHPPL, SRST);
		free(content);
		tk_ptr = tk_ptr->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
