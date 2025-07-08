/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:09:50 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/12/03 13:48:12 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Compares characters from two strings
 * 
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @return Returns an int less than, equal to, or greater than zero.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] - s2[i] == 0)
			i++;
		else
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
