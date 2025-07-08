/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:57:19 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/25 17:18:38 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free (lst);
}

/* static void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}
void delete_content(void *content)
{
    free(content);
}
int	main(void)
{
	t_list	*node3;
	t_list	*node2;
	t_list	*node1;
	t_list	*head;

	node1 = ft_lstnew("Node 1");
	if(node1 == NULL)
	{
		printf("Failed\n");
		return (1);
	}
	node2 = ft_lstnew("Node 2");
	if(node2 == NULL)
	{
		printf("Failed\n");
		return (1);
	}
	node3 = ft_lstnew("Node 3");
	if(node3 == NULL)
	{
		printf("Failed\n");
		return (1);
	}
	head = node1;
	node1->next = node2;
	node2->next = node3;
	printf("List before 'del'\n");
	print_list(head);
	printf("Linked list after using 'del'\n");
	ft_lstdelone(node2, delete_content);
	node1->next = node3;
	print_list(head);
	free(node1->content);
	free(node1);
	free(node3->content);
	free(node3);
	return (0);
} */