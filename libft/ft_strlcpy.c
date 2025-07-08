/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:52:06 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/15 19:52:06 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies strings while ensuring that the destination buffer is 
 * not overflowed.
 * 
 * @param dst A pointer to the destination string
 * @param src A pointer to the source string
 * @param size Size of destination buffer, including the space for '\0'
 * @return Returns the total lenght of the string that was created.
 */
int	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	length;

	if (!dst || !src)
		return (0);
	length = ft_strlen(src);
	if (size == 0)
		return (length);
	i = 0;
	while (src[i] != '\0' && (i < size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (length);
}

/* int	main(void)
{
	char	src[] = "test this";
	char	dest[] = "this space is blank";

	ft_strlcpy(dest, src, sizeof(src));
	printf("%s", dest);
	return (0);
} */