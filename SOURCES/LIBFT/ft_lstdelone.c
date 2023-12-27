/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:25:34 by fpinho-d          #+#    #+#             */
/*   Updated: 2022/12/03 18:07:23 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
static void	del(void *content)
{
	content = NULL;
	free(content);
}
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
/*
int main()
{
	t_list	*Teste;
	char a[] = "Filipe";
	Teste = ft_lstnew(a);
	printf("%s\n", (char *) Teste->content);
	ft_lstdelone(Teste, &del);
	printf("%s\n", (char *) Teste->content);
}
*/
