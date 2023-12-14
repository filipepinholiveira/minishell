/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5ms_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/13 23:10:39 by antoda-s         ###   ########.fr       */
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

	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
}

/// @brief 				Creates a new token
/// @param string		String to be tokenized
/// @param size			Token size
/// @param type			Token type (as per enum t_token_type)
/// @return				New token
t_token	*create_token(const char *string, int size, t_token_type type)
{
	t_token	*token;

	show_func(__func__, MY_START);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_substr(string, 0, size);
	token->size = size;
	token->type = type;
	token->next = NULL;
	show_func(__func__, SUCCESS);
	return (token);
}

/// @brief 				Adds new token to token list end
/// @param head		Head of the token list
/// @param new		New token to be added
void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
}

/// @brief 			Searches for a token type by token char set
/// @param s		String to be searched for token char set
/// @return			Struct with token type information: token char set, size
///					and token type
t_ops	search_token_type(const char *s)
{
	t_ops	ex_ops[12];
	t_ops	blank;
	int				i;

	show_func(__func__, MY_START);
	blank = (t_ops){0, 0, 0};
	ex_ops[0] = (t_ops){">>", 2, TOKEN_R_OUT};
	ex_ops[1] = (t_ops){"<<", 2, TOKEN_R_IN};
	ex_ops[2] = (t_ops){"|", 1, TOKEN_PIPE};
	ex_ops[3] = (t_ops){">", 1, TOKEN_R_OUT};
	ex_ops[4] = (t_ops){"<", 1, TOKEN_R_IN};
	ex_ops[5] = (t_ops){" ", 1, TOKEN_WS};
	ex_ops[6] = (t_ops){"\n", 1, TOKEN_WS};
	ex_ops[7] = (t_ops){"\v", 1, TOKEN_WS};
	ex_ops[8] = (t_ops){"\t", 1, TOKEN_WS};
	ex_ops[9] = (t_ops){"\r", 1, TOKEN_WS};
	ex_ops[10] = (t_ops){"\f", 1, TOKEN_WS};
	ex_ops[11] = (t_ops){NULL, 1, 0};
	i = -1;

	// if (s)
	// 	printf("s token = %s\n", s);
	// else
	// 	printf("s is empry\n");
	while (ex_ops[++i].op)
	{
		if (!ft_strncmp(s, ex_ops[i].op, ex_ops[i].size))
		{
			show_func(__func__, SUCCESS);
			return (ex_ops[i]);
		}
	}
	show_func(__func__, ERROR);
	return (blank);
}

/// @brief 				Initializes the token_getter
/// @param str			String to be tokenized
/// @param head			Head of the token list
/// @return				1 if success, 0 if error
int	token_getter(char *str, t_token **head)
{
	show_func(__func__, MY_START);
	t_ops	curr;
	char	*prev;

	prev = str;
	while (str && *str)
	{
		curr = search_token_type(str);
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
			show_func(__func__, ERROR);
			return (0);
		}	//	return (0);
		else
			++str;
	}
	if (prev != str)
		add_token(head, create_token(prev, str - prev, TOKEN_NAME));
	show_func(__func__, SUCCESS);
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

	show_func(__func__, MY_START);
	if (!token_getter(*line, head))
	{
		show_func(__func__, ERROR);
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
	show_func(__func__, SUCCESS);
	return (0);
}
