/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:25:16 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/12/02 16:55:50 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}
	return (current);
}
/*
int main()
{
	t_list *primeiro;
	t_list *segundo;
	t_list *terceiro;
	char a[] = "Filipe";
	char b[] = "Andre";
	char c[] = "Oliveira";
	primeiro = ft_lstnew(&a);
	segundo = ft_lstnew(&b);
	primeiro->next = segundo;
	terceiro = ft_lstnew(&c);
	segundo->next = terceiro;
	printf("%s\n", (char *) primeiro->content);
	printf("%s\n", (char *) segundo->content);
	printf("%s\n", (char *) terceiro->content);
	primeiro = ft_lstlast(primeiro);
	printf("%s\n", (char *) primeiro->content);
}
*/
