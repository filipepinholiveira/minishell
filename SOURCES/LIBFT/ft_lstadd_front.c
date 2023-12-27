/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:42:01 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/12/02 15:31:02 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int main()
{
	t_list *lst;
	t_list *new;
	char a[] = "Primeiro";
	char b[] = "Novo";
	lst = ft_lstnew(&a);
	new = ft_lstnew(&b);
	printf("%s\n", (char *) lst->content);
	printf("%s\n", (char *) new->content);
	ft_lstadd_front(&lst, new);
	printf("%p\n", lst->next);
	printf("%p\n", new->next);
	printf("%s", (char *) lst->content);
}
*/
