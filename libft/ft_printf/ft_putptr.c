/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:51:54 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/11/12 17:09:39 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putpointerhex(unsigned long n)
{
	char	*base;
	int		result;

	result = 0;
	base = "0123456789abcdef";
	if (n >= 16)
	{
		result += ft_putpointerhex(n / 16);
		result += ft_putpointerhex(n % 16);
	}
	else
		result += write (1, &base[n], 1);
	return (result);
}

int	ft_putptr(void *n)
{
	int				result;
	unsigned long	nbr;

	nbr = (unsigned long)n;
	result = 0;
	if (!nbr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	result += ft_putstr("0x");
	if (nbr == 0)
		result += ft_putchar(0);
	else
		result += ft_putpointerhex(nbr);
	return (result);
}
