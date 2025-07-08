/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:16:58 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/28 15:09:58 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* void f(void *str)
{
	char **s = (char **)str;
	free(*s);
	*s = strdup("changed");
} */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
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
	printf("List before iteration:\n\n");
	print_list(head);
	printf("Linked list after iteration:\n\n");
	ft_lstiter(head, f);
	print_list(head);
	free(node1->content);
	free(node1);
	free(node2->content);
	free(node2);
	free(node3->content);
	free(node3);
	return (0);
} */