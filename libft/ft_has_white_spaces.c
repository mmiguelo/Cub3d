/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_white_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:51:09 by frbranda          #+#    #+#             */
/*   Updated: 2025/07/24 18:02:53 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a string contains only whitespace characters.
 * 
 * @param s The input string to check.
 * @return 1 if the string contains only whitespace, 0 otherwise.
 */
int	ft_has_white_spaces(char *s)
{
	const char	*white_space;
	int			i;

	white_space = " \t\r\n\v\f";
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!ft_strchr(white_space, s[i]))
			return (0);
		i++;
	}
	return (1);
}
