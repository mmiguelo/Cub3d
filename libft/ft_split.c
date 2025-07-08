/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:46:27 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 14:24:42 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of segments within a string delimited by a 'c'
 * 
 * @param s The string to look
 * @param c The delimiter character
 * @return The amount of elements
 */
static int	ft_count_elements(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
			words++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (words);
}

/**
 * @brief counts the number of chars within a string, 
 * until the delimiter is found
 * 
 * @param s The string to look
 * @param c The delimiter character
 * @return The amount fo chars
 */
static int	ft_count_letters(char const *s, char c)
{
	int	i;
	int	letters;

	i = 0;
	letters = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		letters++;
		i++;
	}
	letters++;
	return (letters);
}

/**
 * @brief Copies a string for 'a' amount of chars to an empty string
 * 
 * @param s The string to copy
 * @param a The amount of chars to copy
 * @return Returns the pointer to the string copied 
 */
static char	*ft_copy_words(char const *s, int a)
{
	char	*str;

	str = ft_calloc(a, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s, a);
	return (str);
}

/**
 * @brief Frees the memory of an array char by char
 * 
 * @param s The array to free
 * @param i The number os chars to free
 * @return Returns NULL
 */
static char	**ft_free_mem(char const **s, int i)
{
	while (i > 0)
	{
		i--;
		free((void *)s[i]);
	}
	free (s);
	return (NULL);
}

/**
 * @brief Returns an array of strings obtained by splitting ’s’ using the
 * character ’c’ as a delimiter.
 *
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings resulting from the split or NULL if the
 * allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**array;
	int		line;
	int		column;
	int		i;

	if (!s)
		return (NULL);
	column = ft_count_elements(s, c);
	array = ft_calloc(column + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (column--)
	{
		while (*s && *s == c)
			s++;
		line = ft_count_letters(s, c);
		array[i] = ft_copy_words((char const *) s, line);
		if (!array[i])
			return (ft_free_mem((const char **) array, i));
		i++;
		while (*s && *s != c)
			s++;
	}
	return (array);
}

/* int	main()
{
	char	*str = "Hi, my name is Marco!";
	int		i = 0;
	
	printf("Before doing split:\n%s\n", str);
	char **result = ft_split(str, ' ');
	if (!result)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	while (result[i] != NULL)
	{
		printf("Substring %d: %s\n", i, result[i]);
        free(result[i]);
        i++;
	}
	free (result);
} */
