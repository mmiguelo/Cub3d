/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:31:49 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 13:53:25 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills a block of memory with a specific value.
 * 
 * @param s A pointer to the block of memory to be filled.
 * @param c The value to set.
 * @param n The number of bytes to set.
 * @return Returns a pointer to the memory.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (ptr);
}

/* int	main(void)
{
	char	str[20] = "XXXXXXXXXXXXXXX";
	
	printf("str before memset: %s\n", str);
	ft_memset(str, 'A', 3);
	printf("str after memset: %s\n", str);
	ft_memset(str + 3, 'B', 3);
	printf("str after memset: %s\n", str);
	ft_memset(str + 6, 'C', 3);
	printf("str after memset: %s\n", str);
} */