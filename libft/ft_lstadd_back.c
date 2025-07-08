/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:19:44 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/28 14:54:52 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
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

int	main(void)
{
	t_list	*node2;
	t_list	*node1;
	t_list	*head;
	t_list	*node3;

	node2 = ft_lstnew("Node 2");
	if(node2 == NULL)
	{
		printf("Failed\n");
		return (1);
	}
	node1 = ft_lstnew("Node 1");
	if(node1 == NULL)
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
	printf("Linked list before adding last node:\n");
	print_list(head);
	printf("Linked list after adding node1 to the back:\n");
	ft_lstadd_back(&head, node3);
	print_list(head);
	free(node1);
	free(node2);
	free(node3);
	return (0);
} */