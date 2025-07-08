/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:19:02 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/29 18:51:55 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		del(temp->content);
		temp->content = NULL;
		free(temp);
	}
	*lst = NULL;
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
	printf("List before 'clear'\n");
	print_list(head);
	printf("Linked list after using 'clear'\n");
	ft_lstclear(&head, delete_content);
	print_list(head);
	return (0);
} */