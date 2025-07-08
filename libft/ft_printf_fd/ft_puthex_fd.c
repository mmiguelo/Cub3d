/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:53:22 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:53:24 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_puthex_fd(unsigned int n, char c, int fd)
{
	char	*base;
	int		result;

	result = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		result += ft_puthex_fd((n / 16), c, fd);
		result += ft_puthex_fd((n % 16), c, fd);
	}
	else
		result += write (fd, &base[n], 1);
	return (result);
}
