/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:44:15 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/03/20 14:21:21 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief extracts a substring from a given string.
 * 
 * @param s The original string from which you want to extract a substring.
 * @param start The starting index from which to begin extraction.
 * @param len The lenght of the substring.
 * @return Returns the substring or NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	if (len == 0)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

/* int	main(void)
{
	char	*str = "test in this string";
	int		start = 0;
	size_t	lenght = ft_strlen(str);

	printf("Original string: %s\n", str);
	printf("The substring: %s", ft_substr(str, start, lenght));
	return (0);
} */