/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:51:26 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:51:28 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a deep copy of a matrix of integer pointers.
 *
 * This function duplicates each individual int pointer by allocating
 * a new int and copying the value. The matrix is terminated with a NULL pointer.
 *
 * @param matrix An array of int pointers (int **).
 * @return A newly allocated deep-copied matrix, or NULL on allocation failure.
 */
int	**ft_matrix_dup_int(int **matrix)
{
	int	**dup;
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (matrix[len])
		len++;
	dup = ft_calloc((len + 1), sizeof(int *));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = ft_calloc(1, sizeof(int *));
		if (!dup[i])
		{
			ft_matrix_free((void ***)(&dup));
			return (NULL);
		}
		*dup[i] = *matrix[i];
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
