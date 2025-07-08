/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:51:43 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/29 16:23:30 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n number of bytes from one memory location to another
 * 
 * @param dest A pointer to the destination memory.
 * @param src A pointer to the source memory.
 * @param n The number of bytes to copy.
 * @return Returns a pointer to the destination
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (!n || (!d && !s))
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/* int	main(void)
{
	const char	*src = "Test this copy";
	char		dest[20];
	
	ft_memcpy(dest, src, ft_strlen(src));
	dest[ft_strlen(src)] = '\0';
	printf("Source: %s\n", src);
    printf("Destination after memcpy: %s\n", dest);
	ft_bzero(dest, ft_strlen(src));
	ft_memcpy(dest, src, ft_strlen(src) - 7);
	printf("Destination after memcpy with less bytes to copy: %s\n", dest);
} */