/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:45:47 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 13:40:39 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n bytes from one memory location to another, handling 
 * overlapping regions safely
 * 
 * @param dest A pointer to the destination memory.
 * @param src A pointer to the source memory.
 * @param n The number of bytes to copy.
 * @return Returns a pointer to the destination
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *) src;
	d = (unsigned char *) dest;
	if (!dest || !src)
		return (0);
	if (s < d)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
		ft_memcpy(d, s, n);
	return (d);
}

/* int	main(void)
{
	
	char	dest[50] = "str before doing memmove";
	char	*src = "sucess";

	printf("Test when there isnt overlapping: %s\n", dest);
	ft_memmove(dest, src, 6);
	printf("After memmove: %s\n", dest);
	
	strcpy(dest, "str before doing memmove");
	
	printf("test 2 when there is overlapping (src before dest): %s\n", dest);
	ft_memmove(dest + 10, dest, 5);
	printf("After memmove: %s\n", dest);
	
	strcpy(dest, "str before doing memmove");
	
	printf("test 3 when there is overlapping (dest before src): %s\n", dest);
	ft_memmove(dest, dest + 10, 5);
	printf("After memmove: %s\n", dest);
	
	strcpy(dest, "str before doing memmove");
	
	printf("test 4 when n = 0: %s\n", dest);
	ft_memmove(dest, src, 0);
	printf("After memmove: %s\n", dest);
	
	printf("test 5 whith no dest or src: %p\n", ft_memmove(NULL, NULL, 5));
	
	return (0);
} */