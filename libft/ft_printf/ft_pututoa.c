/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pututoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:31:07 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/11/12 16:53:21 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_intlenght(unsigned int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_pututoa(unsigned int n)
{
	char	*str;
	size_t	lenght;
	int		result;

	result = 0;
	lenght = ft_intlenght(n);
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!str)
		return (0);
	str[lenght] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		lenght--;
		str[lenght] = (n % 10) + 48;
		n = n / 10;
	}
	result = ft_putstr(str);
	free(str);
	return (result);
}
