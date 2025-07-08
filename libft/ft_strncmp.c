/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:02:37 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 16:56:46 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares a specified number of characters from two strings
 * 
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string
 * @param n Maximum number of characters to compare
 * @return Returns an int less than, equal to, or greater than zero.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && (s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

/* int	main(void)
{
	const char	*s1 = "Bom dia";
	const char	*s2 = "Bom dia";
	const char	*s3 = "Boa noite";
	const char	*s4 = "Bom!";
	size_t	n = 7;

	printf("Comparing s1 and s2 which are identical str:\n");
	printf("%d", ft_strncmp(s1, s2, n)); //should be 0
	printf("\nComparing s1 and s3 which are different strings:\n");
	printf("%d", ft_strncmp(s1, s3, n)); // should be positive
	printf("\nComparing s1 and s4 which are different\
	lenghts (same content in first 3 chars):\n");
	printf("%d", ft_strncmp(s1, s4, n)); // should be negative
} */