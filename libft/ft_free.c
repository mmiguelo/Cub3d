/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:50:50 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:50:54 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a dynamically allocated string and sets the original pointer to
 * NULL in the caller.
 *
 * This function safely releases a `char *` and avoids dangling pointers by
 * nullifying it via reference.
 *
 * @param s A pointer to the string to be freed.
 */
void	ft_free(char **s)
{
	if (!s || !*s)
		return ;
	free(*s);
	*s = NULL;
}
