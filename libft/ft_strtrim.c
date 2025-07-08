/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:45:50 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 17:16:46 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checksif a character 'c' is in set.
 * 
 * @param c The character to look.
 * @param set String to be searched.
 * @return Returns 1 if found, or 0 if not found.
 */
int	ft_look_for_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Removes the characters from set in the beginning and end of string.
 * 
 * @param s1 String to search.
 * @param set Set of characters to remove.
 * @return char* Copy of s1.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char		*new;
	size_t		i;
	size_t		start;
	size_t		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_look_for_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_look_for_set(s1[end - 1], set))
		end--;
	new = ft_calloc(end - start + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (start < end)
	{
		new[i] = s1[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}

/* int	main(void)
{
	char	*str = " *bush* test in this str *bush* ";
	char	*set = " *bush* ";

	printf("original string: %s\n", str);
	printf("After trimming: %s\n", ft_strtrim(str, set));
	return (0);
} */