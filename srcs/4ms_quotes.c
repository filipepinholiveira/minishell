/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4ms_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/01/22 18:02:37 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		check if string enclosing quotes are single or double
/// @param str	string to check
/// @return		1 if single quotes (' '), 0 if double quotes (" ")
///				MISLEADING CHANGE STATUS
int	first_quote(char *str)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	i = 0;
	while (str[i] && !(str[i] == '\'' || str[i] == '\"'))
		i++;
	if (str[i] == '\'')
		return (1);
	show_func(__func__, SUCCESS, NULL);
	return (0);
}

/// @brief 		Check if the #quotation marks before index is odd or even.
/// @param str	string to check
/// @param i	termination index
/// @param c	quotation mark to check
/// @return		1 if #quotation before index i is odd, 0 if even
///				MISLEADING CHANGE STATUS
int	odd_before(char **split, int i, char c)
{
	show_func(__func__, MY_START, NULL);
	// show_func(__func__, SHOW_MSG, ft_strjoin("currente split = ", split[i]));
	// show_func(__func__, SHOW_MSG, ft_strjoin("i     = ", ft_itoa(i)));
	// show_func(__func__, SHOW_MSG, ft_charjoin("c     = ", c));

	int	count;
	int	j;

	count = 0;
	while (i--)
	//while (i)
	{
		j = 0;
		//show_func(__func__, SHOW_MSG, ft_strjoin("previous split = ", split[i]));
		while (split[i] && split[i][j])
		{
			// printf("%s%s -> 11 split[%d][%d} = %c%s\n", SBHRED, __func__, i, j, split[i][j], SRST);
			if (split[i][j] == c)
				count++;
			j++;
		}
		/******/
		//i--;
		/******/
	}
	// show_func(__func__, SHOW_MSG, ft_strjoin("N of quotes = ", ft_itoa(count % 2)));
	show_func(__func__, SUCCESS, NULL);
	return (count % 2);
}

/// @brief 		Check if the #quotation marks after index is odd or even.
/// @param str	string to check
/// @param i	termination index
/// @param c	quotation mark to check
/// @return		1 if is odd, 0 if even
///				MISLEADING CHANGE STATUS
int	odd_after(char **str, int i, char c)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("split = ", *str));
	show_func(__func__, SHOW_MSG, ft_strjoin("i     = ", ft_itoa(i)));
	show_func(__func__, SHOW_MSG, ft_charjoin("c     = ", c));

	int	count;
	int	j;

	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i][j])
		{
			if (str[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	show_func(__func__, SHOW_MSG, ft_strjoin("N of quotes = ", ft_itoa(count % 2)));
	show_func(__func__, SUCCESS, NULL);
	return (count % 2);
}

/// @brief 			Copies string contents between quotes
/// @param start 	Pointer at start quote
/// @param end 		pointer at end quote
/// @param str 		destination string
/// @param i 		destination index ?? NEEDS REFACTOR with LIBFT
void	copy_in_quotes(char *start, char *end, char **str, int *i)
{
	show_func(__func__, MY_START, NULL);
	while (start != end)
	{
		(*str)[*i] = *start;
		start++;
		(*i)++;
	}
	show_func(__func__, SUCCESS, NULL);
}

/// @brief 		advances the given pointer to the next character that it is on
///				For example, if the function is called with the pointer pointing
///				at a quotation mark, it will advance the pointer in the string
///				to the next occurence of that same quotation mark. The function
///				returns 0 if this character is never met, which would signify
///				an unclosed quotation mark.
/// @param str	string to advance
/// @return		0 if unclosed quotation mark (error), 1 otherwise (success)
///				MISLEADING CHANGE STATUS
int	closed_quotes_check(char **str)
{
	show_func(__func__, MY_START, NULL);
	char	open_quote;

	open_quote = **str;
	++(*str);
	while (**str && **str != open_quote)
		++(*str);
	if (!**str || (**str != open_quote))
	{
		show_func(__func__, ERROR, "unclosed quotation mark");
		return (0);
	}
	show_func(__func__, SUCCESS, "closed quotation mark");
	return (1);
}

/// @brief 		cleanup after removing redundant quotes and frees up alloc
/// @param tmp	string to clean up
/// @param copy	string to clean up
/// @param i	termination index
/// @return		resulting cleanded string
char	*end_remove_quotes(char *tmp, char *copy, int i)
{
	char	*ret;

	show_func(__func__, MY_START, NULL);
	tmp[i] = '\0';
	ret = ft_strdup(tmp);
	ft_free(tmp);
	ft_free(copy);
	show_func(__func__, SUCCESS, NULL);
	return (ret);
}

/// @brief 		removes redundant quotes
/// @param str	string to remove quotes
/// @return		string clean of quotes
char	*remove_quotes(char *str)
{
	char	*tmp;
	char	*copy;
	char	*start;
	int		i;

	show_func(__func__, MY_START, NULL);
	i = 0;
	copy = str;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tmp)
		return (NULL);
	while (str && *str)
	{
		if (*str == '\"' || *str == '\'')
		{
			start = str + 1;
			closed_quotes_check(&str);
			copy_in_quotes(start, str, &tmp, &i);
		}
		else
			tmp[i++] = *str;
		str++;
	}
	show_func(__func__, SUCCESS, NULL);
	return (end_remove_quotes(tmp, copy, i));
}
