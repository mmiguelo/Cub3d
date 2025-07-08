/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:47:18 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/25 15:46:06 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	last = temp;
	return (last);
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
	t_list	*last;

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
	node1->next = node2;
	head = node1;
	printf("order list:\n");
	print_list(head);
	printf("Last node is:\n");
	last = ft_lstlast(head);
	printf("%s\n", (char *)last->content);
	free(head);
	free(node2);
	return (0);
} */