/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:52:27 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/15 19:52:27 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of a character in a string.
 * 
 * @param s A pointer to the string.
 * @param c The character to locate.
 * @return Returns the pointer to the first occurence or NULL if not found
 */
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = (char *)s;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (cpy + i);
	return (NULL);
}

/* int main(void)
{
	char	*str = "test this string";
	int		c = 'h';
	int		c2 = 'x';

	printf("String before: %s\n", str);
	printf("searching for h:%s\n", ft_strchr(str, c));
	printf("searching for x:%s\n", ft_strchr(str, c2));
} */