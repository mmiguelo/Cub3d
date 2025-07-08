/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:49:43 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/29 10:49:43 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a given character is alphanumeric
 * 
 * @param c The character to be checked
 * @return Returns a non-zero value if true and zero if false
 */
int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/* int	main(void)
{
	int	c;
	int	c2;

	c = 'B';
	c2 = '\n';
	printf("alphanumerical:");
	printf("\n%d\n", ft_isalnum(c));
	printf("non alphanumerical:");
	printf("\n%d\n", ft_isalnum(c2));
	return (0);
} */