/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:51:59 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:52:01 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
	{
		ft_free(&s1);
		ft_free(&s2);
		return (NULL);
	}
	joined = ft_strjoin(s1, s2);
	ft_free(&s1);
	ft_free(&s2);
	return (joined);
}
