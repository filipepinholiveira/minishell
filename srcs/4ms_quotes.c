/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4ms_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/31 10:55:40 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		fetchs for closed / unclosed quotes type " or '
///				the function must be called with the arg str (string)
///				starting with at a quotation mark.
///				The function seeks for the next occurrence of that quation mark
///				and sets str pointer to that next occurrence if found
///				or sets str pointer to the end {\0}
///				@malloc	: NOTHING
///				@free	: NOTHING
/// @param str	addres of teh string to seek, that starts with a quotation mark
/// @return		ERROR (unclosed), SUCCES (closed)
int	tk_quotes_checker(char **str)
{
	show_func(__func__, MY_START, NULL);
	char *tmp;

	tmp = *str;
	(*str) = ft_strchr((*str) + 1, **str);
	if (!(*str))
	{
		(*str) = tmp + ft_strlen(tmp);
		show_func(__func__, ERROR,
			ft_strjoin("unclosed quotation mark : ", ft_substr(tmp, 0, 1)));
		return (ERROR);
	}
	show_func(__func__, SUCCESS, "closed quotation mark");
	return (SUCCESS);
}


/// @brief 		Unquotes a string. Special rules applies
///				- removes ' from limits = 'string'
///				- removes " from limts = "string", "string, string"
///				- (')  and (") are never inspected inside string
///				@malloc	: NOTHING
///				@free	: NOTHING
/// @param str	String to be unquoted
/// @return		A new unquoted string
char	*tk_xpd_unquote(char *str)
{
	show_func(__func__, MY_START, str);
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(str);
	if (str[0] == '\'' || (str[0] == '\"' && str[len - 1] == '\"'))
		ret = ft_substr(str, 1, len - 2);
	else if (str[0] == '\"' && str[len - 1] != '\"')
		ret = ft_strdup(str + 1);
	else if (str[0] != '\"' && str[len - 1] == '\"')
		ret = ft_substr(str, 0, len - 1);
	else if (str[0] != '\"' && str[len - 1] != '\"')
		ret = ft_strdup(str);
	free(str);
	show_func(__func__, SUCCESS, ret);
	return (ret);
}