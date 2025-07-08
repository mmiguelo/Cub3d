/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:57:06 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/28 14:17:16 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*one;

	one = (t_list *)malloc(sizeof(t_list));
	if (!one)
		return (NULL);
	one->content = content;
	one->next = NULL;
	return (one);
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
	t_list	*node1;
	t_list	*head;

	head = NULL;
	print_list(head);
	node1 = ft_lstnew("Node 1");
	if(node1 == NULL)
	{
		printf("Failed\n");
		return (1);
	}
	head = node1;
	printf("Linked list after adding node1\n");
	print_list(head);
	free(node1);
	return (0);
} */