/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:51:41 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:51:44 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a dynamically allocated NULL-terminated matrix of strings.
 *
 * @param matrix A pointer to a matrix (void***) to free and NULL out.
 */
void	ft_matrix_free(void ***matrix)
{
	int	i;

	if (!(*matrix))
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free (*matrix);
	*matrix = NULL;
}
