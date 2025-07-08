/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:51:32 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 14:26:05 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief compares two blocks of memory byte by byte.
 * 
 * @param s1 A pointer to the first block of memory.
 * @param s2 A pointer to the second block of memory.
 * @param n The number of bytes to compare.
 * @return Returns an int less than, equal to, or greater than zero.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (str1[i] == str2[i] && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}

/* int	main(void)
{
	const char	*s1 = "Bom dia";
	const char	*s2 = "Bom dia";
	const char	*s3 = "Boa noite";
	const char	*s4 = "Bom!";
	size_t	n = 7;

	printf("Comparing memory between s1 and s2 which are identical str:\n");
	printf("%d", ft_memcmp(s1, s2, n)); //should be 0
	printf("\nComparing memory between s1 and s3 which\
	 are different strings:\n");
	printf("%d", ft_memcmp(s1, s3, n)); // should be positive
	printf("\nComparing memory between s1 and s4 which are different\
	 lenghts (same content in first 3 chars):\n");
	printf("%d", ft_memcmp(s1, s4, n)); // should be negative
} */