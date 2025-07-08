/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:45:58 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/29 10:49:37 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sets a block of memory to zero - '\0'
 * 
 * @param s A pointer to the memory area to be zeroed
 * @param n The number of bytes to set to zero
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (s == NULL || n == 0)
		return ;
	str = (unsigned char *) s;
	i = 0;
	while (n--)
	{
		str[i] = '\0';
		i++;
	}
}

/* int	main(void)
{
	char str[50] = "ola";
	int	i = 0;
	int len = 4;

	printf("Str before bzero:");
	printf("\n%s\n", str);
	printf("Str after bzero:");
	ft_bzero(str, 4);
	printf("\n");
	while (i < len)
	{
		printf("%d", str[i]);
		i++;
	}
} */