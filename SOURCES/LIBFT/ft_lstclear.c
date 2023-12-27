/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:15:05 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/12/05 15:18:50 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
static void	del(void *content)
{
	content = NULL;
	free (content);
}
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
/*
int main()
{
	t_list	*primeiro;
	t_list	*segundo;
	t_list *terceiro;

	char a[] = "Filipe";
	char b[] = "Andre";
	char c[] = "Oliveira";

	primeiro = ft_lstnew(a);
	segundo = ft_lstnew(b);
	terceiro = ft_lstnew(c);
	primeiro->next = segundo;
	segundo->next = terceiro;
	printf("%p\n", terceiro->next);
	printf("%s\n", (char *)primeiro->content);
	printf("%d\n", ft_lstsize(primeiro));
	ft_lstclear(&primeiro, &del);
	printf("%d\n", ft_lstsize(primeiro));
	primeiro = ft_lstnew(a);
	printf("%s\n", (char *)primeiro->content);
}
*/
