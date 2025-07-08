/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:52:20 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/15 19:52:20 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief concatenates strings while ensuring that the destination buffer 
 * is not overflowed.
 * 
 * @param dst A pointer to the destination string
 * @param src A pointer to the source string
 * @param size Size of destination buffer, including the space for '\0'
 * @return Returns the total lenght of the string that was created.
 */
size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	length_src;
	size_t	length_dst;

	length_src = ft_strlen(src);
	if (!dst && size == 0)
		return (length_src);
	length_dst = ft_strlen(dst);
	j = length_dst;
	i = 0;
	if (size > 0 && length_dst < size - 1)
	{
		while (src[i] && length_dst + i < size - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = '\0';
	}
	if (length_dst >= size)
		length_dst = size;
	return (length_dst + length_src);
}

/* int	main(void)
{
	char dest[20] = "Hello";
	char *source = " World!";

	ft_strlcat(dest, source, sizeof(dest));
	printf("%s", dest);
	return(0);
} */