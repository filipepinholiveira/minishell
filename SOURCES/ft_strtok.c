/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:00:39 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/11/15 17:45:38 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int is_delim(char c, char *delim)
{
    while(*delim != '\0')
    {
        if(c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

char *ft_strtok(char *src_str, char *delim)
{
    static char *backup_str; // inicio da proxima busca
    char *ret;

    if (!src_str)
        src_str = backup_str;
    if (!src_str)
        return (NULL);

    // tratar inicio da string enquanto tem delim

    while (1)
    {
        if (is_delim(*src_str, delim))
        {
            src_str++;
            continue;
        }
        if (*src_str == '\0')
            return (NULL);
        break;
    }
    ret = src_str;
    while (1)
    {
        if (*src_str == '\0')
        {
            //a string acabou e a proxima exec retorna null
            backup_str = src_str;
            return ret;
        }
        if (is_delim(*src_str, delim))
        {
            *src_str = '\0';
            backup_str = src_str + 1;
            return (ret);
        }
        src_str++;
    }

}
