/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:11:57 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 15:19:03 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates suficient memory to hold a copy of the string to duplicate.
 * 
 * @param s A pointer to the string to be duplicate
 * @return char* 
 */
char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy((char *) dest, (char *) s, ft_strlen(s) + 1);
	return (dest);
}

/* int	main(void)
{
	char	*src;
	char	*dest;

	src = "test this string";
	dest = ft_strdup(src);
	printf("%s", dest);
} */