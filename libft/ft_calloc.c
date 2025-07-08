/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:44:36 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/29 10:49:41 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates continuosly dynamic memory.
 * 
 * @param nmemb Number of elements to allocate.
 * @param size Number of bytes to allocate.
 * @return Returns a pointer to the allocated memory.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if ((nmemb > 2147483647 && size != 0) || (size > 2147483647 && nmemb != 0))
		return (NULL);
	ptr = malloc (nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero (ptr, nmemb * size);
	return (ptr);
}

/* int main(void) 
{
    size_t num_elements = 5;
    size_t size_of_element = sizeof(int);
	int	len = 5;
	int i = 0;
	
    // Call ft_calloc
    int *arr = (int *)ft_calloc(num_elements, size_of_element);
    
    // Check if allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
	printf("allocating memory for each element of the array:\n");
    while (i < len)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
		i++;
	}
    free(arr);

    return 0;
} */