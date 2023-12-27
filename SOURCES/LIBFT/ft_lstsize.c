/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:14:40 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/12/02 16:14:25 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
/*
int main()
{
	t_list *first;
	t_list *second;
	char a[] = "Filipe"; 
	int b = 2;
	int size;

	first = ft_lstnew(&a);
	second = ft_lstnew(&b);
//	second = NULL;
	first->next = second;
	size = ft_lstsize(first);
	printf("%d", size);

}
*/
