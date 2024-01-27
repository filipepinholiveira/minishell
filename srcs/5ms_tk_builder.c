/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5ms_tk_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/26 16:42:17 by antoda-s         ###   ########.fr       */
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
		if (ptr.op != 0 && prev != str)
			tk_lst_addback(tk_lst, tk_addnew(prev, str - prev, TK_NAME));
		if (ptr.op != 0)
		{
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
		tk_lst_addback(tk_lst, tk_addnew(prev, str - prev, TK_NAME));
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
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
		return (return_error("Syntax Error", 0));
	}
	show_token_list(*token);
	tk_ptr = *token;
	while (tk_ptr)
	{
		content = tk_ptr->content;
		tk_ptr->content = env_var_expander(content, s->envp);
		free(content);
		tk_ptr = tk_ptr->next;
	}
	show_func(__func__, SUCCESS, NULL);
	return (0);
}
