/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_pp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:51:45 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/01 15:46:49 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* void	**ft_realloc_pp(void **ptr, size_t original_size, size_t new_size)
{
	void	**new_ptr;
	int		i;

	i = 0;
	new_ptr = malloc(new_size * sizeof(void *));
    if (!new_ptr)
        return (NULL);
	while (i < original_size && i < new_size)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	while (i < new_size)
		new_ptr[i++] = NULL;
	free(ptr);
	return (new_ptr);
} */
