/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:47:33 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 17:56:05 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*temp_node;
	void	*function;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	temp_node = NULL;
	while (lst)
	{
		function = f(lst->content);
		temp_node = ft_lstnew(function);
		if (!temp_node)
		{
			del(function);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, temp_node);
		lst = lst->next;
	}
	return (new_list);
}

/* static void *to_uppercase(void *content)
{
    char *str = (char *)content;
    char *new_str = malloc(ft_strlen(str) + 1);
    if (!new_str)
		return (NULL);
    int i = 0;
	while (str[i])
	{
    	if (str[i] >= 'a' && str[i] <= 'z')
			new_str[i] = str[i] - 32;
		else
			new_str[i] = str[i];
   		i++;
	}
    new_str[ft_strlen(str)] = '\0';
    return (new_str);
}

static void	print_list(t_list *lst)
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
	t_list	*node3 = ft_lstnew("Node 3");
	t_list	*node2 = ft_lstnew("Node 2");
	t_list	*node1 = ft_lstnew("Node 1");
	t_list	*head;

	head = node1;
	node1->next = node2;
	node2->next = node3;

	printf("List before 'map':\n");
	print_list(head);
	t_list *mapped_list = ft_lstmap(head, to_uppercase, delete_content);
	printf("List after 'map':\n");
	print_list(mapped_list);
	return (0);
} */