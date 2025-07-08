/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:51:39 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/29 15:08:48 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of a character in a block of memory.
 * 
 * @param s A pointer to the block of memory.
 * @param c The character to be located.
 * @param n The number of bytes to search within that memory.
 * @return Returns a pointer to the first occurrence of the character c in the 
 * memory block pointed to by s. If the character is not found within the 
 * first n bytes, it returns NULL
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chr;
	size_t			i;

	if (!s)
		return (0);
	str = (unsigned char *) s;
	chr = (unsigned char) c;
	i = -1;
	while (++i < n)
	{
		if (str[i] == chr)
			return (&str[i]);
	}
	return (0);
}

/* int	main(void)
{
	const char	*str = "Bom dia!";
	char		c = 'm';
	size_t		n = strlen(str);
	
	char	*result = ft_memchr(str, c, n);

	if (result)
		printf("Character '%c' found at position: %ld\n", c, result - str);
	else
		printf("Character '%c' not found in the string.\n", c);
	return (0);
} */
