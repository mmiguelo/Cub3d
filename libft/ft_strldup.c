/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:52:06 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:52:09 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates up to 'length' characters from the input string.
 * Depending if len of s or length is bigger.
 * 
 * @param s A pointer to the source string to be duplicated.
 * @param length The maximum number of characters to copy from the source.
 * @return A pointer to the newly allocated string, or NULL on 
 * allocation failure.
 */
char	*ft_strldup(const char *s, int length)
{
	char	*dup;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	if (len > length)
		len = length;
	dup = (char *)ft_calloc((len + 1), sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
