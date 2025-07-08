/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:33:40 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/01 14:51:33 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Reallocates memory to a new size, copying the old data.
 * 
 * @param ptr The pointer to the previously allocated memory.
 * @param original_size The size of the original allocated memory block.
 * @param new_size The size of the new memory block.
 * @return void* A pointer to the newly allocated memory block, or NULL if
 * allocation fails.
 */
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new_ptr;
	size_t	i;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	i = original_size;
	if (new_size < original_size)
		i = new_size;
	ft_memcpy(new_ptr, ptr, i);
	free(ptr);
	return (new_ptr);
}
