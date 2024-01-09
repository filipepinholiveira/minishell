/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5ms_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/09 13:28:06 by antoda-s         ###   ########.fr       */
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
		if (head->type != TOKEN_PIPE && head->next && !head->next->content[0])
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
t_token	*create_token(const char *string, int size, t_token_type type)
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

/// @brief 				Adds new token to token list end
/// @param head		Head of the token list
/// @param new		New token to be added
void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	show_func(__func__, MY_START, NULL);
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	show_func(__func__, SUCCESS, NULL);
}

/// @brief 			Searches for a token type by token char set
/// @param s		String to be searched for token char set
/// @return			Struct with token type information: token char set, size
///					and token type
t_ops	token_type_getter(const char *s)
{
	show_func(__func__, MY_START, NULL);
	t_ops		blank;
	int			i;
	const t_ops	ops[13] = {{">>", 2, TOKEN_R_OUT}, {"<<", 2, TOKEN_R_IN},
	{"|", 1, TOKEN_PIPE}, {">", 1, TOKEN_R_OUT}, {"<", 1, TOKEN_R_IN},
	{" ", 1, TOKEN_WS}, {"\n", 1, TOKEN_WS}, {"\v", 1, TOKEN_WS},
	{"\t", 1, TOKEN_WS}, {"\r", 1, TOKEN_WS}, {"\f", 1, TOKEN_WS},
	{"=", 1, TOKEN_EQUAL}, {NULL, 1, 0}};

	blank = (t_ops){0, 0, 0};
	i = -1;
	while (ops[++i].op)
	{
		if (!ft_strncmp(s, ops[i].op, ops[i].size))
		{
			show_func(__func__, SUCCESS, ft_strjoin("Found token: ", (char *)ops[i].op));
			//show_func(__func__, SUCCESS, "MESSAGE");
			return (ops[i]);
		}
	}
	show_func(__func__, ERROR, "Character is not a TOKEN");
	return (blank);
}

/// @brief 				Initializes the token_getter
/// @param str			String to be tokenized
/// @param head			Head of the token list
/// @return				1 if success, 0 if error
int	token_getter(char *str, t_token **head)
{
	t_ops	curr;
	char	*prev;

	show_func(__func__, MY_START, NULL);
	prev = str;
	while (str && *str)
	{
		curr = token_type_getter(str);
		if (curr.op != 0 && prev != str)
			add_token(head, create_token(prev, str - prev, TOKEN_NAME));
		if (curr.op != 0)
		{
			str += curr.size;
			if (curr.type != TOKEN_WS)
				add_token(head, create_token(curr.op, curr.size, curr.type));
			prev = str;
		}
		else if ((*str == '\"' || *str == '\'') && !treat_quotes(&str))
		{
			show_func(__func__, ERROR, NULL);
			return (0);
		}
		else
			++str;
	}
	if (prev != str)
		add_token(head, create_token(prev, str - prev, TOKEN_NAME));
	show_func(__func__, SUCCESS, NULL);
	return (1);
}

/// @brief 				Trims the token command from whitespaces
/// @param line_buffer	string input with script
/// @param head			pointer to the head of the token list
/// @param script		script structure
/// @return				SUCCESS if valid, ERROR if invalid
int	tokenize(char **line, t_token **head, t_script *script)
{
	t_token	*tmp;
	char	*bis;

	show_func(__func__, MY_START, NULL);
	if (!token_getter(*line, head))
	{
		show_func(__func__, ERROR, NULL);
		return (return_error("Syntax Error", 0));
	}
	tmp = *head;
	while (tmp)
	{
		bis = tmp->content;
		tmp->content = replace_env_var(bis, script->envp, 0, 0);
		free(bis);
		tmp = tmp->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
// t_ops	token_type_getter(const char *s)
// {
// 	show_func(__func__, MY_START, NULL);
// 	t_ops	ops[13];
// 	t_ops	blank;
// 	int		i;

// 	blank = (t_ops){0, 0, 0};
// 	ops[0] = (t_ops){">>", 2, TOKEN_R_OUT};
// 	ops[1] = (t_ops){"<<", 2, TOKEN_R_IN};
// 	ops[2] = (t_ops){"|", 1, TOKEN_PIPE};
// 	ops[3] = (t_ops){">", 1, TOKEN_R_OUT};
// 	ops[4] = (t_ops){"<", 1, TOKEN_R_IN};
// 	ops[5] = (t_ops){" ", 1, TOKEN_WS};
// 	ops[6] = (t_ops){"\n", 1, TOKEN_WS};
// 	ops[7] = (t_ops){"\v", 1, TOKEN_WS};
// 	ops[8] = (t_ops){"\t", 1, TOKEN_WS};
// 	ops[9] = (t_ops){"\r", 1, TOKEN_WS};
// 	ops[10] = (t_ops){"\f", 1, TOKEN_WS};
// 	ops[11] = (t_ops){"=", 1, TOKEN_EQUAL};
// 	ops[11] = (t_ops){NULL, 1, 0};
// 	i = -1;
// 	while (ops[++i].op)
// 	{
// 		if (!ft_strncmp(s, ops[i].op, ops[i].size))
// 		{
// 			show_func(__func__, SUCCESS, (char *)ops[i].op);
// 			return (ops[i]);
// 		}
// 	}
// 	show_func(__func__, ERROR, "Character is not a TOKEN");
// 	return (blank);
// }