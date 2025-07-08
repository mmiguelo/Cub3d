/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:51:57 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/15 19:51:57 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief determines the length of a null terminated string.
 * 
 * @param str A pointer to the string to calculate the length.
 * @return Returns the number of characters in the string.
 */
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/* int	main(void)
{
	char	*str;

	str = "this str has length of 25";
	printf("%s\n", str);
	printf("length is: %zu", ft_strlen(str));
	return (0);
} */