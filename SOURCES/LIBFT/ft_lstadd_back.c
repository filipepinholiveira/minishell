/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:59:59 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/12/02 19:21:44 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nova;

	nova = *lst;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	nova = ft_lstlast(*lst);
	nova->next = new;
}
/*
int main()
{
	t_list *lst;
	t_list *new;
	char a[] = "primeiro";
	char b[] = "segundo";
	lst = ft_lstnew(&a);
	new = ft_lstnew(&b);
	printf("%p\n", (char *)lst->next);
	printf("%p\n", (char *) new->next);
	ft_lstadd_back(&lst, new);
	printf("%p\n", (char *)lst->next);
	printf("%p\n", (char *) new->next);
}
*/
